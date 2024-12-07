package HTTPServer;

import java.io.*;
import java.net.*;


public class HTTPFileServer {
    private static final int PORT = 5042;
    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server is listening on port " + PORT);

            while (true) {
                Socket socket = serverSocket.accept();
                //System.out.println("Connected");
                Thread clientHandler=new ClientHandler(socket);
                clientHandler.start();
            }
        } catch (IOException e) {
            System.out.println("Server exception: " + e.getMessage());
        }
    }
}
