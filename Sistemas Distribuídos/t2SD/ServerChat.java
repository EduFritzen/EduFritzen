import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Scanner;

// Implementação do servidor de chat
public class ServerChat extends UnicastRemoteObject implements IServerChat {
    private ArrayList<String> roomList; // Lista de salas

    // Construtor do servidor de chat
    protected ServerChat() throws RemoteException {
        roomList = new ArrayList<>();
    }

    // Método para obter a lista de salas disponíveis
    @Override
    public synchronized ArrayList<String> getRooms() throws RemoteException {
        return new ArrayList<>(roomList); // Retorna uma cópia da lista de salas para evitar alterações externas
    }

    // Método para criar uma nova sala de chat
    @Override
    public synchronized void createRoom(String roomName) throws RemoteException {
        if (!roomList.contains(roomName)) {
            roomList.add(roomName); // Adiciona a nova sala à lista de salas
            RoomChat room = new RoomChat(roomName); // Cria uma nova instância da sala de chat
            Registry registry = LocateRegistry.getRegistry(2020);
            registry.rebind(roomName, room); // Registra a nova sala no registro RMI
        }
    }

    // Método para fechar uma sala de chat existente
    public synchronized void closeRoom(String roomName) throws RemoteException {
        if (roomList.contains(roomName)) {
            try {
                Registry registry = LocateRegistry.getRegistry(2020);
                IRoomChat room = (IRoomChat) registry.lookup(roomName);
                room.closeRoom(); // Fecha a sala de chat
                registry.unbind(roomName); // Remove a sala do registro RMI
                roomList.remove(roomName); // Remove a sala da lista local de salas
                System.out.println("Room " + roomName + " closed.");
            } catch (Exception e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("Room " + roomName + " not found.");
        }
    }

    // Método principal para iniciar o servidor de chat
    public static void main(String[] args) {
        try {
            LocateRegistry.getRegistry(2020); // Inicializa o registro RMI na porta 2020
            ServerChat server = new ServerChat();
            Registry registry = LocateRegistry.getRegistry(2020);
            registry.rebind("Servidor", server); // Registra o servidor no registro RMI com o nome "Servidor"
            System.out.println("Servidor de Chat iniciado.");

            Scanner scanner = new Scanner(System.in);
            while (true) {
                System.out.println("Digite o nome da sala para fechar ou 'exit' para sair:");
                String roomName = scanner.nextLine();
                if (roomName.equalsIgnoreCase("exit")) {
                    break; // Sai do loop se o usuário digitar 'exit'
                }
                server.closeRoom(roomName);
            }
            scanner.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

