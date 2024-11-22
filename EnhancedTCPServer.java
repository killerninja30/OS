package src;

import java.io.*;
import java.net.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class EnhancedTCPServer {
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(65432);
            System.out.println("Server listening on port 65432...");

            Socket clientSocket = serverSocket.accept();
            System.out.println("Connected to client: " + clientSocket.getInetAddress());

            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            // Send greeting message to the client
            String greeting = "Welcome to the Server! Type 'bye' to end the conversation.";
            out.println(greeting);

            String clientMessage;
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

            // Continuously listen for messages until client says 'bye'
            while ((clientMessage = in.readLine()) != null) {
                System.out.println("[" + dtf.format(LocalDateTime.now()) + "] Client: " + clientMessage);

                // End conversation if client sends "bye"
                if (clientMessage.equalsIgnoreCase("bye")) {
                    out.println("Goodbye! Connection will be closed.");
                    break;
                }

                // Send response back to the client
                String response = "Server received: " + clientMessage;
                out.println("[" + dtf.format(LocalDateTime.now()) + "] " + response);
            }

            clientSocket.close();
            serverSocket.close();
            System.out.println("Connection closed.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

