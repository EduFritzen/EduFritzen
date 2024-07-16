import java.rmi.Remote;
import java.rmi.RemoteException;

// Interface para usuário de chat, define métodos que podem ser invocados remotamente
public interface IUserChat extends Remote {
    void deliverMsg(String senderName, String msg) throws RemoteException; // Entrega mensagem ao usuário
}

