import socket
import pickle

def calcular_crc(dados):
    crc16 = 0xFFFF
    poly = 0x8005

    for byte in dados:
        crc16 ^= (byte << 8)
        for _ in range(8):
            if crc16 & 0x8000:
                crc16 = (crc16 << 1) ^ poly
            else:
                crc16 <<= 1

    return crc16 & 0xFFFF

cliente_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 12345)

try:
    cliente_socket.connect(server_address)
    print('Conexão estabelecida com o servidor.')

    # Lê as mensagens de um arquivo de texto
    with open('mensagens.txt', 'r') as arquivo:
        frames = arquivo.read().splitlines()

    window_size = 4
    base = 0
    next_seq_num = 0
    received_acks = set()

    while base < len(frames):
        # Envia os quadros dentro da janela de transmissão
        for i in range(base, min(base + window_size, len(frames))):
            if i not in received_acks:
                frame = {
                    'numero': i,
                    'dados': frames[i]
                }
                frame['crc'] = calcular_crc(frame['dados'].encode())

                try:
                    cliente_socket.send(pickle.dumps(frame))
                    print('Enviado quadro:', i)
                except socket.error as e:
                    print('Erro ao enviar quadro:', i)
                    print('Detalhes do erro:', str(e))

        try:
            cliente_socket.settimeout(10)  # Define um tempo limite para a recepção do ACK
            while True:
                try:
                    ack = pickle.loads(cliente_socket.recv(1024))
                    print('Recebido ACK:', ack)
                    if ack >= base:
                        received_acks.add(ack)
                        base = ack + 1
                        break
                except socket.timeout:
                    print('Timeout: Reenviando quadros...')
                    break
                except pickle.UnpicklingError:
                    print('Erro ao decodificar o ACK recebido.')
        except socket.timeout:
            print('Timeout: Nenhum ACK recebido.')
        except socket.error as e:
            print('Erro na comunicação com o servidor.')
            print('Detalhes do erro:', str(e))
            break

    cliente_socket.close()
    print('Conexão encerrada com o servidor.')

except socket.error as e:
    print('Erro ao conectar ao servidor.')
    print('Detalhes do erro:', str(e))
