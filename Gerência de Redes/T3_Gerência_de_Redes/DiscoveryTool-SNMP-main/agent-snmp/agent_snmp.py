from pysnmp.entity import engine, config
from pysnmp.entity.rfc3413 import cmdrsp, context
from pysnmp.carrier.asynsock.dgram import udp
from pysnmp.smi import builder

import threading
import collections

MibObject = collections.namedtuple('MibObject', ['mibName', 'objectType', 'valueFunc', 'valueSetFunc'])

class Mib(object):
    """Armazena os valores da MIB customizada"""

    def __init__(self):
        self._lock = threading.RLock()
        self._historico_descobertas = "Historico de descobertas da ferramenta"      # historicoDeDescobertas OBJECT, type OCTET STRING
        self._intervalo_verificacao = 1000                                          # intervaloDeVerificacao OBJECT, type Integer32 (1..1440)

    """
    historico_descoberta tem OID  = 1.3.6.1.3.5.1
    intervalo_verificacao tem OID   = 1.3.6.1.3.5.2
    """

    def getHistoricoDescobertas(self):
        return self._historico_descobertas
    
    def setHistoricoDescobertas(self, value):
        with self._lock:
            self._historico_descobertas = value

    def getIntervaloVerificacao(self):
        return self._intervalo_verificacao
    
    def setIntervaloVerificacao(self, value):
        with self._lock:
            self._intervalo_verificacao = value

def createVariable(SuperClass, getValue, setValue, *args):
    """Cria uma instancia da variável que será enviada para o gerente.
    getValue => função para recuperar o valor da variável;
    setValue => funçao para definir o valor da variável;
    """
    class Var(SuperClass):
        def readGet(self, name, *args):
            print("Getting obj")
            return name, self.syntax.clone(getValue())

        def writeCommit(self, name, val, *args):
            print("Setting obj...")
            setValue(val)
    
    return Var(*args)

class SNMPAgent(object):
    """Implementação do Agent que serve a MIB da ferramenta de descoberta"""

    def __init__(self, mibObjects):
        """Lista dos objetos que o Agent irá utilizar"""
        self._snmpEngine = engine.SnmpEngine()
        config.addSocketTransport(self._snmpEngine, udp.domainName, udp.UdpTransport().openServerMode(('', 161)))

        # Configura duas Strings de Comunidade
        config.addV1System(self._snmpEngine, "read-agent", "public")
        config.addV1System(self._snmpEngine, "write-agent", "private")

        # Permite acesso 'public' para leitura
        config.addVacmUser(self._snmpEngine, 2, "read-agent", "noAuthNoPriv", readSubTree=(1,3,6,1,3,5))

        # Permite acesso 'private' para leitura/escrita
        config.addVacmUser(self._snmpEngine, 2, "write-agent", "noAuthNoPriv", readSubTree=(1,3,6,1,3,5), writeSubTree=(1,3,6,1,3,5))

        # Cria o contexto do Agent
        self._snmpContext = context.SnmpContext(self._snmpEngine)

        # Importa a MIB
        mibBuilder = self._snmpContext.getMibInstrum().getMibBuilder()
        mibSources = mibBuilder.getMibSources() + (builder.DirMibSource('.'),)
        mibBuilder.setMibSources(*mibSources)

        MibScalarInstance, = mibBuilder.importSymbols('SNMPv2-SMI', 'MibScalarInstance')

        # Exporta a MIB customizada
        for mibObject in mibObjects:
            nextVar, = mibBuilder.importSymbols(mibObject.mibName, mibObject.objectType)

            instance = createVariable(MibScalarInstance, 
                                      mibObject.valueFunc, 
                                      mibObject.valueSetFunc, 
                                      nextVar.name, (0,), 
                                      nextVar.syntax)
            
            instanceDict = {str(nextVar.name) + "Instance":instance}
            mibBuilder.exportSymbols(mibObject.mibName, **instanceDict)
        
        # Informa ao PySNMP como responder aos Get, Set, GetNext e GetBulk
        cmdrsp.GetCommandResponder(self._snmpEngine, self._snmpContext)
        cmdrsp.SetCommandResponder(self._snmpEngine, self._snmpContext)
        cmdrsp.NextCommandResponder(self._snmpEngine, self._snmpContext)
        cmdrsp.BulkCommandResponder(self._snmpEngine, self._snmpContext)

    def serve_forever(self):
        print("Starting agent")
        self._snmpEngine.transportDispatcher.jobStarted(1)
        try:
            self._snmpEngine.transportDispatcher.runDispatcher()
        except:
            self._snmpEngine.transportDispatcher.closeDispatcher()
            raise

if __name__ == '__main__':
    mib = Mib()
    objects = [MibObject('FERRAMENTA-DE-DESCOBERTA-MIB', 'intervaloDeVerificacao', mib.getIntervaloVerificacao, mib.setIntervaloVerificacao),
               MibObject('FERRAMENTA-DE-DESCOBERTA-MIB', 'historicoDeDescobertas', mib.getHistoricoDescobertas, mib.setHistoricoDescobertas)]
    
    agent = SNMPAgent(objects)

    try:
        agent.serve_forever()
    except KeyboardInterrupt:
        print("Shutting down")
