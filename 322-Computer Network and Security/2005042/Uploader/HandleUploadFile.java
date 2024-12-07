package Uploader;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class HandleUploadFile extends Thread {
    private File file;
    private static final int CHUNK_SIZE = 1024;

    public HandleUploadFile(File file) throws IOException {
        this.file = file;
    }

    @Override
    public void run() {
        try (Socket socket = new Socket(Client.serverAddress, Client.serverPort);
             OutputStream out = socket.getOutputStream();
             InputStream fileInput = new FileInputStream(file)) {
            byte[] buffer = new byte[CHUNK_SIZE];
            int bytesRead;
            PrintWriter serverWrite=new PrintWriter(out,true);
            serverWrite.println("UPLOAD " + file.getName());
            while ((bytesRead = fileInput.read(buffer)) != -1) {
                out.write(buffer, 0, bytesRead);
                out.flush();
            }
            System.out.println("File " + file.getName() + " uploaded successfully.");
            socket.close();
            System.out.println("Connection closed");
        } catch (Exception e) {
            System.out.println("Error uploading file: "+e);
        }

    }
}
