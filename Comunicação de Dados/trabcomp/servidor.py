import socket
import pickle
import time

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

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 12345)
timeout = 10  # Tempo limite em segundos
max_duplicate_frames = 3  # Número máximo de quadros duplicados permitidos

try:
    server_socket.bind(server_address)
    server_socket.listen(1)
    print('Servidor pronto para receber conexões.')

    client_socket, addr = server_socket.accept()
    print('Conexão estabelecida com o cliente:', addr)

    expected_frame_no = 0
    acknowledged_frames = []  # Quadros confirmados pelo cliente
    start_time = time.time()  # Tempo de início para controle de timeout
    duplicate_frame_count = 0  # Contador de quadros duplicados

    # Definir o tempo limite para o socket do cliente
    client_socket.settimeout(timeout)

    while True:
        try:
            data = client_socket.recv(1024)
            if not data:
                break

            try:
                received_frame = pickle.loads(data)
                print('Quadro válido recebido:', received_frame)

                if received_frame['numero'] == expected_frame_no and calcular_crc(received_frame['dados'].encode()) == received_frame['crc']:
                    if received_frame['numero'] not in acknowledged_frames:
                        print('Enviando ACK:', expected_frame_no)
                        client_socket.send(pickle.dumps(expected_frame_no))
                        acknowledged_frames.append(expected_frame_no)
                    else:
                        print('Recebido quadro duplicado, já foi confirmado. Enviando ACK:', received_frame['numero'])
                        client_socket.send(pickle.dumps(received_frame['numero']))
                        duplicate_frame_count += 1

                    expected_frame_no += 1
                    # Reinicializa o timer para o próximo quadro esperado
                    start_time = time.time()
                elif received_frame['numero'] < expected_frame_no:
                    print('Recebido quadro duplicado, enviando ACK:', received_frame['numero'])
                    client_socket.send(pickle.dumps(received_frame['numero']))
                    duplicate_frame_count += 1
                else:
                    print('Quadro fora de ordem, ignorando e aguardando próximo quadro.')

                print('Aguardando próximo quadro...')
                continue

            except pickle.UnpicklingError:
                print('Erro ao decodificar o quadro recebido.')
        except socket.timeout:
            print('Timeout: Nenhum dado recebido.')
        except socket.error as e:
            print('Erro na comunicação com o cliente.')
            print('Detalhes do erro:', str(e))
            break

        # Verifica se algum quadro não foi confirmado dentro do intervalo de timeout
        if len(acknowledged_frames) > 0 and time.time() - start_time > timeout:
            print('Timeout: Quadros não confirmados. Reenviando...')
            for frame in range(expected_frame_no, expected_frame_no + len(acknowledged_frames)):
                client_socket.send(pickle.dumps(frame))

        # Verifica se a quantidade máxima de quadros duplicados foi alcançada
        if duplicate_frame_count >= max_duplicate_frames:
            print('Número máximo de quadros duplicados alcançado. Encerrando conexão...')
            break

    client_socket.close()
    server_socket.close()
    print('Conexão encerrada com o cliente.')

except socket.error as e:
    print('Erro ao iniciar o servidor.')
    print('Detalhes do erro:', str(e))
