import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

// Implementação do cliente de chat
public class UserChat extends UnicastRemoteObject implements IUserChat, ActionListener {
    private String usrName; // Nome do usuário
    private IServerChat server; // Referência ao servidor de chat
    private IRoomChat currentRoom; // Referência à sala atual

    // Interface gráfica
    private JTextArea chatArea; // area de texto para mensagens
    private JTextField messageField; // Campo de entrada de mensagem
    private JList<String> roomList; // Lista de salas disponíveis
    private DefaultListModel<String> roomListModel; // Modelo da lista de salas

    // Construtor do cliente de chat
    protected UserChat(String usrName) throws RemoteException {
        super();
        this.usrName = usrName;
    }

    // Método para receber uma mensagem de um usuário ou do sistema
    @Override
    public void deliverMsg(String senderName, String msg) throws RemoteException {
        chatArea.append(senderName + ": " + msg + "\n"); // Adiciona a mensagem a area de chat
        if (msg.equals("Sala fechada pelo servidor.")) {
            currentRoom = null; // Remove a referência à sala atual
            chatArea.append("Você foi desconectado.\n");
            updateRoomList(); // Atualiza a lista de salas disponíveis
            enableUIComponents(true); // Habilita os componentes da interface do usuário
        }
    }

    // Método para inicializar a interface gráfica do cliente de chat
    private void initUI() {
        JFrame frame = new JFrame("Chat Room");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(600, 400);

        // area de chat
        chatArea = new JTextArea();
        chatArea.setEditable(false);
        frame.add(new JScrollPane(chatArea), BorderLayout.CENTER);

        // Campo de mensagem e botão Enviar
        JPanel bottomPanel = new JPanel();
        messageField = new JTextField(20);
        JButton sendButton = new JButton("Enviar");
        sendButton.addActionListener(this);
        bottomPanel.add(messageField);
        bottomPanel.add(sendButton);
        frame.add(bottomPanel, BorderLayout.SOUTH);

        // Lista de salas e botões
        JPanel sidePanel = new JPanel(new BorderLayout());
        roomListModel = new DefaultListModel<>();
        roomList = new JList<>(roomListModel);
        sidePanel.add(new JScrollPane(roomList), BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        JButton joinButton = new JButton("Entrar");
        joinButton.addActionListener(this);
        JButton leaveButton = new JButton("Sair");
        leaveButton.addActionListener(this);
        JButton createButton = new JButton("Criar");
        createButton.addActionListener(this);
        JButton refreshButton = new JButton("Atualizar");
        refreshButton.addActionListener(this);
        buttonPanel.add(joinButton);
        buttonPanel.add(leaveButton);
        buttonPanel.add(createButton);
        buttonPanel.add(refreshButton);
        sidePanel.add(buttonPanel, BorderLayout.SOUTH);

        frame.add(sidePanel, BorderLayout.EAST);

        // Conectar ao servidor e atualizar lista de salas
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 2020);
            server = (IServerChat) registry.lookup("Servidor");
            updateRoomList();
        } catch (Exception e) {
            e.printStackTrace();
        }

        frame.setVisible(true);
    }

    // Método para atualizar a lista de salas disponíveis na interface gráfica
    private void updateRoomList() {
        try {
            ArrayList<String> rooms = server.getRooms();
            roomListModel.clear(); // Limpa o modelo da lista de salas
            for (String room : rooms) {
                roomListModel.addElement(room); // Adiciona cada sala à lista
            }
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    // Método para habilitar ou desabilitar os componentes da interface gráfica
    private void enableUIComponents(boolean enable) {
        messageField.setEnabled(enable);
    }

    // Método de tratamento de eventos para os botões da interface gráfica
    @Override
    public void actionPerformed(ActionEvent e) {
        String command = e.getActionCommand();
        switch (command) {
            case "Enviar":
                sendMessage(); // Envia uma mensagem
                break;
            case "Entrar":
                joinRoom(); // Entra em uma sala de chat
                break;
            case "Sair":
                leaveRoom(); // Sai da sala de chat
                break;
            case "Criar":
                createRoom(); // Cria uma nova sala de chat
                break;
            case "Atualizar":
                updateRoomList(); // Atualiza a lista de salas
                break;
        }
    }

    // Método para enviar uma mensagem para a sala de chat atual
    private void sendMessage() {
        if (currentRoom != null) {
            String message = messageField.getText();
            if (!message.isEmpty()) {
                try {
                    currentRoom.sendMsg(usrName, message); // Envia a mensagem para a sala de chat
                    messageField.setText(""); // Limpa o campo de mensagem após o envio
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    // Método para entrar em uma sala de chat
    private void joinRoom() {
        String roomName = roomList.getSelectedValue();
        if (roomName != null) {
            try {
                Registry registry = LocateRegistry.getRegistry("localhost", 2020);
                IRoomChat room = (IRoomChat) registry.lookup(roomName);
                room.joinRoom(usrName, this); // Solicita entrada na sala de chat ao servidor
                currentRoom = room; // Define a sala de chat atual
                chatArea.setText("Você entrou na sala " + roomName + "\n"); // Exibe uma mensagem na área de chat
                enableUIComponents(true); // Habilita os componentes da interface gráfica
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    // Método para sair da sala de chat atual
    private void leaveRoom() {
        if (currentRoom != null) {
            try {
                currentRoom.leaveRoom(usrName); // Solicita saída da sala de chat ao servidor
                currentRoom = null; // Remove a referência à sala de chat atual
                chatArea.setText("Você saiu da sala.\n"); // Exibe uma mensagem na área de chat
                enableUIComponents(true); // Habilita os componentes da interface gráfica
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    // Método para criar uma nova sala de chat
    private void createRoom() {
        String roomName = JOptionPane.showInputDialog("Digite o nome da nova sala:");
        if (roomName != null && !roomName.isEmpty()) {
            try {
                server.createRoom(roomName); // Solicita ao servidor a criação de uma nova sala de chat
                updateRoomList(); // Atualiza a lista de salas disponíveis na interface gráfica
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    // Método principal para iniciar o cliente de chat
    public static void main(String[] args) {
        try {
            if (args.length < 1) {
                System.out.println("Usage: java UserChat <server_address>");
                return;
            }
            String serverAddress = args[0];
            Registry registry = LocateRegistry.getRegistry(serverAddress, 2020);
            IServerChat server = (IServerChat) registry.lookup("Servidor");

            // Solicitar um nome de usuário único
            String usrName = JOptionPane.showInputDialog("Enter your username:");
            if (usrName == null || usrName.isEmpty()) {
                System.out.println("Nome de usuário não pode ser vazio.");
                return;
            }

            UserChat user = new UserChat(usrName);
            registry.rebind(usrName, user); // Registra o cliente de chat no registro RMI com o nome de usuário
            user.initUI(); // Inicializa a interface gráfica do cliente de chat

            // Mantém o cliente em execução para receber mensagens
            while (true) {
                Thread.sleep(1000); // Verifica mensagens a cada segundo
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
