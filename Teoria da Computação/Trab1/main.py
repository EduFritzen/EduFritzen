class MTR:
    
    def __init__(self):
        self.estados = [] #lista dos estados que a MT pode ter
        self.entradaAlfabeto = [] #símbolos do alfabeto de entrada
        self.saidaAlfabeto = [] #símbolos do alfabeto de saída

        #estado durante a execução
        self.estadoAtual = None
        self.estadoInicial = None
        self.estadoFinal = None

        self.funcoesTransicao = [] #lista de transições possíveis da MT
        self.branco = 'B' # espaço em branco na fita

        self.fitas = self.Fitas()  #objeto com as três fitas (input, history, output)
    
    class Fitas:
        def __init__(self):
            self.input = [] #fita de entrada
            self.history = [] #fita de histórico
            self.output = [] #fita de saída
            
            self.cab_input = 0 #posição da cabeça de leitura/escrita da fita de entrada
            self.cab_history = 0 #posição da cabeça de leitura/escrita da fita de histórico
            
        def mover_cab_input_para_direita(self):
            self.cab_input += 1

        def mover_cab_input_para_esquerda(self):
            self.cab_input -= 1

        def mover_cab_history_para_direita(self):
            self.cab_history += 1

        def mover_cab_history_para_esquerda(self):
            self.cab_history -= 1

    class Transicao:
        def __init__(self, estadoAnterior, simboloEntrada, estadoSeguinte, simboloSaida, direcao):
            #inicializa os atributos da nova transição
            self.estadoAnterior = estadoAnterior
            self.simboloEntrada = simboloEntrada
            self.estadoSeguinte = estadoSeguinte
            self.simboloSaida = simboloSaida
            self.direcao = direcao

            # Quadruplas para representar a Máquina de Turing Reversível
            self.setLeEscreveQuadrupla()
            self.setDeslocamentoQuadrupla()

        def setLeEscreveQuadrupla(self):
            self.quadrupla = {
                'estadoAnterior': self.estadoAnterior, 
                'simboloEntrada': self.simboloEntrada,
                'simboloSaida': self.simboloSaida,
                'estadoTemporario': self.estadoAnterior + "_"
            }
        
        def setDeslocamentoQuadrupla(self):
            self.deslocamentoQuadrupla = {
                'estadoTmp': self.estadoAnterior + "_",
                'espacoEmBranco': '/',
                'direcao': self.direcao,
                'estadoSeguinte': self.estadoSeguinte
            }
          
        # Retorna uma representacao de string do objeto
        def __str__(self):
            return "(" + self.estadoAnterior + "," + self.simboloEntrada + ")=(" + self.estadoSeguinte + "," + self.simboloSaida + "," + self.direcao + ")"

    # Busca uma transição específica na lista de transições
    def buscaTransicao(self, estado, simbolo):
        i = 0
        
        for transicao in self.funcoesTransicao: # Para cada um das transicoes
            if transicao.estadoAnterior == estado and transicao.simboloEntrada == simbolo: 
                return transicao, i # retorna a tupla da transição encontrada e o índice
            i += 1
        exit() # Se a função chega nesse ponto, não houve transição correspondente       
    
    # Configura os estados da MT, adicionando um estado a cada chamada de função
    def configuraEstado(self, label):
        label = label.strip()
        # Se não tiver estado atual, o estado atual, é o inicial
        if self.estadoAtual is None:
            self.estadoInicial = label
            self.estadoAtual = label  
        
        self.estados.append(label) # Label é adicionada a lista de estados
        self.estadoFinal = label # Atualiza
      
    # Configura as transições da MT, adicionando uma transição a cada chamada de função
    def configuraTransicao(self, estadoAnterior, simboloEntrada, estadoSeguinte, simboloSaida, direcao):
        if estadoAnterior in self.estados: # verifica se está na lista de estados da MT
            if estadoSeguinte in self.estados:
                transicao = self.Transicao(estadoAnterior, simboloEntrada, estadoSeguinte, simboloSaida, direcao) #cria uma nova instância
                self.funcoesTransicao.append(transicao) # adiciona na lista de transições
            else:
                exit("estado ", estadoSeguinte, " inexistente")
        else:
            exit("estado ", estadoAnterior, " inexistente")

    # Configura o alfabeto de entrada da MT
    def configuraAlfabetoInput(self, entradaAlfabeto):
        for simbolo in entradaAlfabeto:
            self.entradaAlfabeto.append(simbolo) # adiciona cada símbolo do alfabeto à lista
        self.entradaAlfabeto.append(self.branco) # caractere branco é adicionado no fim
    
    # Configura o alfabeto de saída da MT
    def configuraAlfabetoOutput(self, saidaAlfabeto):
        for simbolo in saidaAlfabeto:
            self.saidaAlfabeto.append(simbolo) # adiciona cada símbolo do alfabeto à lista
    
    # Adiciona caracteres na fita
    def configuraFitaInput(self, fita):
        for simbolo in fita: 
            if simbolo not in self.entradaAlfabeto: # verifica se símbolo da fita não pertence ao alfabeto da MT
                exit("O símbolo ", simbolo, " não pertence ao alfabeto de entrada.")
        
        self.fitas.input = fita # fita da máquina recebe a fita verificada 
        self.fitas.input.append(self.branco) # adiciona o caractere branco no final

    def mover_input_cabecalho(self, direcao, ida): # move a cabeça de leitura/escrita da fita input
        if direcao == 'L' and ida == True:
            self.fitas.mover_cab_input_para_esquerda()
        elif direcao == 'R' and ida == True:
            self.fitas.mover_cab_input_para_direita()
        elif direcao == 'L' and ida == False:
            self.fitas.mover_cab_input_para_direita()
        elif direcao == 'R' and ida == False:
            self.fitas.mover_cab_input_para_esquerda()

    def executaIda(self): #Executa a fase 1 da MTR
        while True:
            # Se o estado atual for o final e a pos do cabecalho da fita de entrada for maior que a propria fita
            if self.estadoAtual == self.estadoFinal and self.fitas.cab_input >= len(self.fitas.input): 
                self.fitas.cab_history = len(self.fitas.history) - 1 # atualiza o cabecalho de history para pos final da fita history, 
                return # não há mais nada para ser lido
                    
            simboloAtual = self.fitas.input[self.fitas.cab_input] # pega o símbolo da cabeça de leitura/escrita da fita input
            
            transicao, indiceTransicao = self.buscaTransicao(self.estadoAtual, simboloAtual) # obtem a transição correspondente ao estado e símbolo atual
            self.fitas.history.append(indiceTransicao) # Adiciona o indice de transicao na fita historico

            print("Fita de Entrada\t", self.fitas.input, "\nHistory\t", self.fitas.history)
            
            # Escreve o simbolo de saida na fita de entrada
            self.fitas.input[self.fitas.cab_input] = transicao.quadrupla['simboloSaida']
          
            # Atualiza o estado atual com o próximo estado obtido a partir da transição
            self.estadoAtual = transicao.deslocamentoQuadrupla['estadoSeguinte']
            self.mover_input_cabecalho(transicao.deslocamentoQuadrupla['direcao'], True) # Avança a cabeça da fita de entrada
            
    def copiaDaEntradaParaSaida(self): #Executa a fase 2 da MTR
        self.fitas.output = self.fitas.input.copy() # Salva a entrada na fita de saida

    def executaVolta(self):
        while True:
            # Se chegou no estado inicial e a pos cabecalho de entrada for 0
            if self.estadoAtual == self.estadoInicial and self.fitas.cab_input == 0:
                return # chegou ao fim
              
            indiceTransicao = self.fitas.history[self.fitas.cab_history] # índice da transição a partir da cabeça de history
            transicao = self.funcoesTransicao[indiceTransicao] # Obtém a transição original a partir do índice

            # Avança a cabeça da fita de acordo com a direção indicada na transição original 
            self.mover_input_cabecalho(transicao.deslocamentoQuadrupla['direcao'], False)
            
            # Fita de entrada recebe o simbolo de entrada de transicao, pois está voltando, lê a primeira parte da transicao
            self.fitas.input[self.fitas.cab_input] = transicao.quadrupla['simboloEntrada']

            # Atualiza o estado atual com o estado anterior
            self.estadoAtual = transicao.quadrupla['estadoAnterior']
          
            print("Fita de Entrada\t", self.fitas.input, "\nHistory\t", self.fitas.history)

            self.fitas.history.pop() # Exclui o último elemento da fita de history, pois está retrocedendo
            self.fitas.mover_cab_history_para_esquerda() # Atualiza a posição do cabeçote de history

    def executaFases(self):
        # Fase 1 da Máquina de Turing Reversivel:
        print("FASE 1 -> COMPUTA DA ESQUERDA PARA A DIREITA:")
        self.executaIda()

        # Fase 2 da Máquina de Turing Reversivel:
        print("\nFASE 2 -> COPIA DA ENTRADA PARA A SAIDA")
        self.copiaDaEntradaParaSaida()

        # Fase 3 da Máquina de Turing Reversivel:
        print("\nFASE 3 -> REVERTE (DIREITA PARA A ESQUERDA):")
        self.executaVolta()

        print("\nConcluido!!!\n")
        print('Fita de Entrada:', self.fitas.input)
        print('Fita de Saída:  ', self.fitas.output)
        print('Histórico funcoes de transicao: ', self.fitas.history)



mt = MTR() # Cria instância da classe MTR

# variaveis da primeira linha do txt
numEstados, inTamAlfabeto, outTamAlfabeto, numTransicoes = [int(i.strip()) for i in input().strip().split(' ')]

estados = input().strip().split(' ') # Variavel que recebe os estados, segunda linha do txt

inputAlfabeto = input().strip().split(' ') # Alfabeto da entrada
mt.configuraAlfabetoInput(inputAlfabeto)

outputAlfabeto = input().strip().split(' ') # Alfabeto de saída
mt.configuraAlfabetoOutput(outputAlfabeto)

for i in range(numEstados): # Adiciona os estados na MTR
    mt.configuraEstado(estados[i])

for i in range(0, numTransicoes): # Adiciona as transicoes na MTR
    _in, _out = input().strip().split('=')
    _in = _in.strip('()').split(',')
    _out = _out.strip('()').split(',')
    mt.configuraTransicao(_in[0], _in[1], _out[0], _out[1], _out[2])

inputFita = list(input().strip()) # Fita de entrada
mt.configuraFitaInput(inputFita)

mt.executaFases() # Chama a funcao que roda a MTR