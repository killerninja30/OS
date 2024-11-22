package src;

import java.io.*;
import java.net.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class EnhancedTCPClient {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("127.0.0.1", 65432);
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            // Read the server's greeting message
            System.out.println(in.readLine());

            Scanner scanner = new Scanner(System.in);
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

            // Allow multiple messages to be sent
            String message;
            while (true) {
                System.out.print("You: ");
                message = scanner.nextLine();
                out.println(message);

                if (message.equalsIgnoreCase("bye")) {
                    System.out.println("Ending conversation...");
                    break;
                }

                // Receive response from the server
                String serverResponse = in.readLine();
                System.out.println("[" + dtf.format(LocalDateTime.now()) + "] " + serverResponse);
            }

            socket.close();
            scanner.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

