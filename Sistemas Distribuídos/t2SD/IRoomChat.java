import java.rmi.Remote;
import java.rmi.RemoteException;

// Interface para sala de chat, define métodos que podem ser invocados remotamente
public interface IRoomChat extends Remote {
    void sendMsg(String usrName, String msg) throws RemoteException; // Envia mensagem para a sala
    void joinRoom(String usrName, IUserChat user) throws RemoteException; // Adiciona usuário à sala
    void leaveRoom(String usrName) throws RemoteException; // Remove usuário da sala
    void closeRoom() throws RemoteException; // Fecha a sala de chat
    String getRoomName() throws RemoteException; // Obtém o nome da sala
}

