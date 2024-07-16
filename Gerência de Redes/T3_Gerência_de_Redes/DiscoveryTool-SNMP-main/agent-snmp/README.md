## CRÉDITOS

[Simple-SNMP-Agent-and-Manager](https://github.com/anushkumar27/Simple-SNMP-Agent-and-Manager/) from anushkumar27
    
Este projeto é uma adaptação do projeto do repositório citado acima.

## REQUISITOS
    
Testei no WSL Ubuntu

* Python3.11
* snmp        -> Ferramentas para testar o agente;
* pysnmp      -> Biblioteca Python do agente;


### Algumas Observações:
Tive que alterar o ID da MIB para 5, então ficou:

~~::= { experimental 1 }~~ -> ::= { experimental 5 }

Os status estavam apresentando erro, então coloquei todos como `current`;

Caso queira / precise realizar qualquer alteração na MIB, será necessário recompilá-la (seguindo o passo-a-passo abaixo).



## COMO COMPILAR A MIB

Considerando a seguinte estrutura de pastas:

    agent-snmp
    |_ mibs_folder
    |    |_ SNMP-FRAMEWORK-MIB.my
    |    |_ SNMPv2-CONF.my
    |    |_ SNMPv2-MIB.my
    |    |_ SNMPv2-SMI.my
    |    |_ SNMPv2-TC.my
    |
    |_ mibdump.py
    |
    |_ agent_snmp.py
    |_ FERRAMENTA-DE-DESCOBERTA-MIB.mib

Dentro da pasta "agent-snmp" execute o seguinte comando:

```
python mibdump.py --mib-source=/home/<user-folder>/agent-snmp/mibs_folder --destination-directory=/home/<user-folder>/agent-snmp --destination-format=pysnmp FERRAMENTA-DE-DESCOBERTA-MIB
```

Após concluir a compilação, deverá aparecer um arquivo como no nome: `FERRAMENTA-DE-DESCOBERTA-MIB.py`



## COMO EXECUTAR O AGENTE

Certifique-se que a porta 161 está livre.
Caso esteja ocupada, edite o script do agente na linha 60:

```
config.addSocketTransport(self._snmpEngine, udp.domainName, udp.UdpTransport().openServerMode(('', <NOVA-PORTA>)))
```

Com a MIB compilada e a porta livre, execute:

```
sudo python agent_snmp.py
```

Se tudo ocorreu certo, a seguinte mensagem aparecerá no terminal: `Starting agent`



## TESTANDO O AGENTE

Utilize o comando:

```
snmpwalk -v2c -c public localhost 1.3.6.1.3.5
```

Ou, caso tenha alterado a porta:

```
snmpwalk -v2c -c public localhost:<NOVA-PORTA> 1.3.6.1.3.5
```

O retorno deve ser:

```
iso.3.6.1.3.5.1.0 = STRING: "Historico de descobertas da ferramenta"
iso.3.6.1.3.5.2.0 = INTEGER: 1000
iso.3.6.1.3.5.2.0 = No more variables left in this MIB View (It is past the end of the MIB tree)
```



## ADICIONANDO NOVOS OBJETOS DA MIB

Para testar, apenas implementei:

* historicoDeDescobertas -> octet string
* intervaloDeVerificacao -> integer32

É necessário implementar o restante dos objetos.
Para isso, é só adicionar um novo atributo na classe Mib do agente.
E criar as funções de Get e Set.

> Basta seguir o padrão dos que já foram implementados.

Após implementar os objetos na classe Mib,
Na lista 'objects' na "main", adicione os objetos seguindo o padrão dos outros.

OBS.: Acredito que para os objetos read-only não necessite da funçao Set, mas não cheguei a testar