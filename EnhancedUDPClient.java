package src;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class EnhancedUDPClient {
    public static void main(String[] args) {
        try {
            DatagramSocket clientSocket = new DatagramSocket();

            InetAddress serverAddress = InetAddress.getByName("127.0.0.1");
            int serverPort = 65432;
            Scanner scanner = new Scanner(System.in);

            String message;
            byte[] sendBuffer;
            byte[] receiveBuffer = new byte[1024];

            while (true) {
                // Read message from user
                System.out.print("You: ");
                message = scanner.nextLine();
                sendBuffer = message.getBytes();

                // Send message to the server
                DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverAddress, serverPort);
                clientSocket.send(sendPacket);
                System.out.println("Sent to server: " + message);

                // Exit if the message is "bye"
                if (message.equalsIgnoreCase("bye")) {
                    System.out.println("Ending conversation...");
                    break;
                }

                // Receive response from the server
                DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
                clientSocket.receive(receivePacket);
                String serverResponse = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("Received from server: " + serverResponse);
            }

            // Close the socket
            clientSocket.close();
            scanner.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

