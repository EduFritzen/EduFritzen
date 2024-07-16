import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

// Implementação da sala de chat
public class RoomChat extends UnicastRemoteObject implements IRoomChat {
    private String roomName; // Nome da sala
    private Map<String, IUserChat> userList; // Lista de usuários na sala
    private ExecutorService executor; // Executor para envio assíncrono de mensagens

    // Construtor da sala de chat
    protected RoomChat(String roomName) throws RemoteException {
        this.roomName = roomName;
        this.userList = new ConcurrentHashMap<>(); // Inicializa a lista de usuários como ConcurrentHashMap para acesso concorrente
        this.executor = Executors.newCachedThreadPool(); // Inicializa o executor de threads
    }

    // Método para adicionar um usuário à sala
    @Override
    public synchronized void joinRoom(String usrName, IUserChat user) throws RemoteException {
        if (!userList.containsKey(usrName)) {
            userList.put(usrName, user);
            sendSystemMessage(usrName + " has joined the room."); // Envia mensagem do sistema informando a entrada do usuário na sala
        }
    }

    // Método para remover um usuário da sala
    @Override
    public synchronized void leaveRoom(String usrName) throws RemoteException {
        if (userList.containsKey(usrName)) {
            userList.remove(usrName);
            sendSystemMessage(usrName + " has left the room."); // Envia mensagem do sistema informando a saída do usuário da sala
        }
    }

    // Método para enviar uma mensagem para todos os usuários na sala
    @Override
    public synchronized void sendMsg(String usrName, String msg) throws RemoteException {
        for (IUserChat user : userList.values()) {
            executor.submit(() -> {
                try {
                    user.deliverMsg(usrName, msg); // Entrega a mensagem ao usuário
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            });
        }
    }

    // Método para fechar a sala de chat
    @Override
    public synchronized void closeRoom() throws RemoteException {
        for (IUserChat user : userList.values()) {
            executor.submit(() -> {
                try {
                    user.deliverMsg("SYSTEM", "Sala fechada pelo servidor."); // Envia mensagem do sistema informando que a sala foi fechada
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            });
        }

        executor.shutdown(); // Encerra o executor de threads
        userList.clear(); // Limpa a lista de usuários
    }

    // Método para obter o nome da sala
    @Override
    public String getRoomName() throws RemoteException {
        return roomName;
    }

    // Método para enviar uma mensagem do sistema para todos os usuários na sala
    private void sendSystemMessage(String msg) throws RemoteException {
        for (IUserChat user : userList.values()) {
            executor.submit(() -> {
                try {
                    user.deliverMsg("SYSTEM", msg); // Envia mensagem do sistema para o usuário
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            });
        }
    }
}

