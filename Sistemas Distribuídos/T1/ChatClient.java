import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException; 
import java.io.PrintWriter; 
import java.net.Socket; 
import java.util.Scanner; 
import java.awt.BorderLayout; 
import java.awt.Color; 
import javax.swing.JFrame; 
import javax.swing.JOptionPane; 
import javax.swing.JScrollPane; 
import javax.swing.JTextField; 
import javax.swing.JTextPane;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

public class ChatClient {

    String serverAddress;
    Scanner in;
    PrintWriter out;
    JFrame frame = new JFrame("Chatter");
    JTextField textField = new JTextField(50);
    JTextPane messagePane = new JTextPane();

    public ChatClient(String serverAddress) {
        this.serverAddress = serverAddress;

        textField.setEditable(false);
        frame.getContentPane().add(textField, BorderLayout.SOUTH);
        frame.getContentPane().add(new JScrollPane(messagePane), BorderLayout.CENTER);
        frame.setSize(600, 400);

        textField.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                out.println(textField.getText());
                textField.setText("");
            }
        });
    }

    private String getName() {
        return JOptionPane.showInputDialog(frame, "Choose a screen name:", "Screen name selection",
                JOptionPane.PLAIN_MESSAGE);
    }

    private void appendMessage(String message, SimpleAttributeSet attributes) {
        StyledDocument doc = messagePane.getStyledDocument();
        try {
            doc.insertString(doc.getLength(), message, attributes);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void run() throws IOException {
    try {
        var socket = new Socket(serverAddress, 59001);
        in = new Scanner(socket.getInputStream());
        out = new PrintWriter(socket.getOutputStream(), true);

        while (in.hasNextLine()) {
            var line = in.nextLine();
            if (line.startsWith("SUBMITNAME")) {
                out.println(getName());
            } else if (line.startsWith("NAMEACCEPTED")) {
                this.frame.setTitle("Chatter - " + line.substring(13));
                textField.setEditable(true);
            } else if (line.startsWith("SYSTEM_MESSAGE")) {
                String message = line.substring(15);
                Color color = Color.RED; 
                if (message.contains("joined")) {
                    color = Color.GREEN;
                }
                SimpleAttributeSet set = new SimpleAttributeSet();
                StyleConstants.setForeground(set, color);
                appendMessage(message + "\n", set); 
            } else if (line.startsWith("MESSAGE")) {
                String message = line.substring(8);
                int colonIndex = message.indexOf(':');
                if (colonIndex > 0) {
                    String name = message.substring(0, colonIndex + 1); 
                    String text = message.substring(colonIndex + 1);

                    SimpleAttributeSet nameSet = new SimpleAttributeSet();
                    StyleConstants.setBold(nameSet, true);
                    StyleConstants.setForeground(nameSet, Color.BLUE); 
                    appendMessage(name, nameSet);


                    SimpleAttributeSet textSet = new SimpleAttributeSet();
                    appendMessage(text + "\n", textSet);
                } else {
                    SimpleAttributeSet set = new SimpleAttributeSet();
                    appendMessage(message + "\n", set);
                }
            }
        }
    } finally {
        frame.setVisible(false);
        frame.dispose();
    }
}

    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.err.println("Pass the server IP as the sole command line argument");
            return;
        }
        var client = new ChatClient(args[0]);
        client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.frame.setVisible(true);
        client.run();
    }
}
