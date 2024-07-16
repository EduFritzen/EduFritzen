import socket
import pickle
import time
import random

# Função para calcular o CRC de um quadro
def calcular_crc(quadro):
    crc = 0xFFFF  # Valor inicial do CRC

    # Converte a mensagem em bytes
    mensagem_bytes = quadro['dados'].encode()

    for byte in mensagem_bytes:
        crc ^= (byte << 8)
        for _ in range(8):
            if crc & 0x8000:
                crc = (crc << 1) ^ 0x1021 #CRC-CCITT
            else:
                crc <<= 1

    return crc & 0xFFFF

# Cria um objeto socket
servidor_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

endereco_servidor = ('127.0.0.1', 2080)
servidor_socket.bind(endereco_servidor)
servidor_socket.listen(1)

print("Servidor pronto para receber conexões.")

# Função para enviar uma confirmação (ACK) ao cliente
def enviar_ack(numero_quadro):
    if quadro_numero_esperado <= numero_quadro < quadro_numero_esperado + max_quadros:
        ack = {'ack': True, 'numero': numero_quadro}
        cliente_socket.send(pickle.dumps(ack))

# Função para enviar uma negação (NAK) ao cliente
def enviar_nak(numero_quadro):
    if quadro_numero_esperado <= numero_quadro < quadro_numero_esperado + max_quadros:
        nak = {'ack': False, 'numero': numero_quadro}
        cliente_socket.send(pickle.dumps(nak))

# Função para receber um quadro do cliente
def receber_quadro():
    quadro_serializado = cliente_socket.recv(1024)
    return pickle.loads(quadro_serializado)

# Função para processar o quadro recebido
def processar_quadro(quadro):
    # Introduz um erro de transmissão modificando um bit aleatoriamente nos dados
    if random.random() < 0.1:  # 10% de probabilidade de quadro inválido
       erro_posicao = random.randint(0, len(quadro['dados']) - 1)
       quadro['dados'] = quadro['dados'][:erro_posicao] + 'X' + quadro['dados'][erro_posicao+1:]
    if calcular_crc(quadro) == quadro['crc']:
        print("Quadro válido recebido:", quadro)
        enviar_ack(quadro['numero'])
    else:
        print("Quadro inválido recebido. CRC não coincide.")
        enviar_nak(quadro['numero'])

# Lê as mensagens de um arquivo de texto
with open('mensagens.txt', 'r') as arquivo:
    mensagens = arquivo.read().splitlines()

# Aceita conexões de clientes
cliente_socket, endereco_cliente = servidor_socket.accept()
print("Conexão estabelecida com:", endereco_cliente)

# Variáveis de controle Go-Back-N ARQ
quadro_numero_esperado = 0
max_quadros = 1

# Recebe e processa os quadros enviados pelo cliente
while True:
    quadro = receber_quadro()
    if quadro_numero_esperado <= quadro['numero'] < quadro_numero_esperado + max_quadros:
        if quadro['numero'] == quadro_numero_esperado:
            processar_quadro(quadro)
            quadro_numero_esperado += 1
        else:
            enviar_ack(quadro_numero_esperado - 1)
            enviar_nak(quadro['numero'])  # Envia um NAK para solicitar o reenvio do quadro
    else:
        enviar_ack(quadro_numero_esperado - 1)

    # Verifica se todos os quadros foram recebidos
    if quadro_numero_esperado == len(mensagens):
        break

   

# Envia ACK final
enviar_ack(quadro_numero_esperado)

# Fecha a conexão
cliente_socket.close()
servidor_socket.close()
