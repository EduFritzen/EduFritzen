from datetime import datetime
from ipaddress import IPv4Network,IPv4Address
from scapy.all import ARP, Ether, srp
from time import sleep
import sys
import json

def set_ip_range(ip, mask):
    # Converte o endereço IP e a máscara de sub-rede em objetos ipaddress.IPv4Network
    network = IPv4Network(f"{ip}/{mask}", strict=False)

    # Encontra o primeiro e o último endereço disponível na rede
    first_ip = network.network_address + 1
    last_ip = network.broadcast_address - 1

    # Retorna os IPs encontrados
    return first_ip, last_ip

def get_mac_address(ip):
    # Converter o IPv4Address para String
    ip_str = str(ip)

    # Cria um pacote ARP com o IP alvo
    arp = ARP(pdst=ip_str)

    # Cria um pacote Ethernet para enviar o ARP
    ether = Ether(dst="ff:ff:ff:ff:ff:ff") # Broadcast MAC address

    # Combina o pacote Ethernet e o ARP
    packet = ether/arp

    # Envia o pacote e obtém a resposta
    result = srp(packet, timeout=1, verbose=False)[0]

    # Retorna o endereço MAC se houver uma resposta
    if result:
        return result[0][1].hwsrc
    else:
        return None

def find_manufacturer(mac_address, vendors):
    for vendor in vendors:
        if vendor.get("macPrefix") == mac_address:
            return vendor
    
    return None

def load_file(path):
    file = open(path, encoding="utf-8")
    lista = json.load(file)
    file.close()

    return lista

def save_file(path, lista):
    file = open(path, 'w', encoding='utf-8')
    json.dump(lista, file, ensure_ascii=False, indent=4)
    file.close()

def is_known(devices, ip):
    for device in devices:
        if device["ip"] == str(ip):
            return device
    
    return None

def main():
    ip = sys.argv[1]    # Endereço IP informado
    mask = sys.argv[2]  # Máscara de sub-rede informada

    # Carregar os MACs dos fabricantes
    vendors = load_file('mac-vendors.json')

    # Encontrar o primeiro e o último IP da rede
    first_ip, last_ip = set_ip_range(ip, mask)

    print(f"Buscando dispositivos na rede [{first_ip} ... {last_ip}]\n")

    while True:
        print(" {:<22} {:<15} {:<19} {}".format("Data da descoberta", "IP", "Endereço MAC", "Fabricante"))
        print("="*90)

        # Carregar histórico de dispositivos
        devices = load_file('devices.json')
        new_devices = []

        # Buscar por cada IP na rede
        current_ip = first_ip
        while current_ip <= last_ip:
            current_device = {
                "state" : None,
                "ip" : str(current_ip),
                "mac" : None,
                "vendor_name" : None,
                "discover_date_time" : None,
                "last_access_date_time" : None
            }

            now = datetime.now()
            data_time = now.strftime("%d/%m/%Y, %H:%M:%S")

            # Buscar IP no histórico
            exist_device = is_known(devices, current_ip)

            # Buscar o MAC do dispositivo e
            # Verificar se está o dispositivo está online
            current_mac_address = get_mac_address(current_ip)

            if current_mac_address:
                # Dispositivo ONLINE
                
                if exist_device:
                    # IP no Histórico

                    if current_mac_address != exist_device["mac"]:
                        # IP no Histórico / Dispositivo mudou - MAC mudou
                        current_vendor = find_manufacturer(current_mac_address[:8].upper(), vendors)

                        current_device["state"] = "changed"
                        current_device["mac"] = current_mac_address["mac"]
                        current_device["vendor_name"] = current_vendor["vendorName"]
                        current_device["discover_date_time"] = data_time
                        current_device["last_access_date_time"] = data_time
                        print("\033[93m {:<22} {:<15} {:<19} {} \033[00m".format(current_device["discover_date_time"], current_device["ip"], current_device["mac"], current_device["vendor_name"]))
                    else:
                        # IP no Histórico / Dispositivo igual - MAC não mudou
                        current_device["state"] = "online"
                        current_device["mac"] = exist_device["mac"]
                        current_device["vendor_name"] = exist_device["vendor_name"]
                        current_device["discover_date_time"] = exist_device["discover_date_time"]
                        current_device["last_access_date_time"] = data_time
                        print("\033[92m {:<22} {:<15} {:<19} {} \033[00m".format(current_device["discover_date_time"], current_device["ip"], current_device["mac"], current_device["vendor_name"]))
                
                else:
                    # IP novo
                    current_vendor = find_manufacturer(current_mac_address[:8].upper(), vendors)

                    current_device["state"] = "new"
                    current_device["mac"] = current_mac_address
                    current_device["vendor_name"] = current_vendor["vendorName"]
                    current_device["discover_date_time"] = data_time
                    current_device["last_access_date_time"] = data_time
                    print("\033[96m {:<22} {:<15} {:<19} {} \033[00m".format(current_device["discover_date_time"], current_device["ip"], current_device["mac"], current_device["vendor_name"]))
                
                new_devices.append(current_device)
        
            else:
                # Dispositivo OFFLINE

                if exist_device:
                    # IP no Histórico
                    current_device["state"] = "offline"
                    current_device["mac"] = exist_device["mac"]
                    current_device["vendor_name"] = exist_device["vendor_name"]
                    current_device["discover_date_time"] = exist_device["discover_date_time"]
                    current_device["last_access_date_time"] = exist_device["last_access_date_time"]

                    print("\033[91m {:<22} {:<15} {:<19} {} \033[00m".format(current_device["discover_date_time"], current_device["ip"], current_device["mac"], current_device["vendor_name"]))
                    new_devices.append(current_device)

            current_ip += 1

        print("\nA verificação terminou! \n")
        save_file('devices.json', new_devices)

        print("Uma nova verificação será executada em 10 min.\nAguardando...\n\n")
        sleep(600) # Espera 10 min. até a próxima verificação
        print("A nova verificação irá começar\n\n")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Uso: python sniffer.py <endereco_ip> <mascara_sub_rede>\nEx.: python sniffer.py 192.168.0.10 255.255.255.0")
        sys.exit(1)
    main()
