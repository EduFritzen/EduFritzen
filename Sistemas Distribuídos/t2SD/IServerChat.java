import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

// Interface para o servidor de chat, define métodos que podem ser invocados remotamente
public interface IServerChat extends Remote {
    ArrayList<String> getRooms() throws RemoteException; // Obtém lista de salas disponíveis
    void createRoom(String roomName) throws RemoteException; // Cria uma nova sala de chat
}

