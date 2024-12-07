package HTTPServer;

import java.io.*;
import java.net.Socket;
import java.util.Objects;

public class ClientHandler extends Thread {
    private Socket socket;
    public static int requestCount=0;
    int CHUNK_SIZE = 1024;
    public ClientHandler(Socket socket) throws IOException {
        this.socket = socket;
    }
    @Override
    public void run() {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             OutputStream out = socket.getOutputStream()) {

            String requestLine = in.readLine();
            if (requestLine != null && requestLine.startsWith("GET")) {
                handleGetRequest(requestLine, out);
            } else if (requestLine != null && requestLine.startsWith("UPLOAD")) {
                handleUploadRequest(requestLine,socket.getInputStream(),out);
            } else{
                System.out.println("Invalid request type");
            }
            socket.close();
            //System.out.println("Connection Closed");
        } catch (IOException e) {
            System.out.println("ClientHandler exception: " + e.getMessage());
        }
    }

    private void handleUploadRequest(String requestLine, InputStream in, OutputStream out) {
        String[] tokens=requestLine.split(" ");
        String uploadDir="root/uploadedFiles";
        String fileName=tokens[1];
        File uploadFile = new File(uploadDir, fileName);
        try (FileOutputStream fileOut = new FileOutputStream(uploadFile)) {
            byte[] buffer = new byte[CHUNK_SIZE];
            int bytesRead;
            while ((bytesRead = in.read(buffer)) != -1) {
                fileOut.write(buffer, 0, bytesRead);
            }
            System.out.println("File " + fileName + " uploaded successfully.");
            //String response=("HTTP/1.0 200 OK\r\n\r\nFile uploaded successfully.\r\n");
        } catch (IOException e) {
            System.out.println("Error writing file: " + e.getMessage());
        }
    }

    private void handleGetRequest(String requestLine, OutputStream out) throws IOException {
        String[] tokens=requestLine.split(" ");
        String path=tokens[1];
        String currentPath="root"+path;
        String response;
        File file=new File(currentPath);
        if(file.isDirectory()){
            response=showListOfFiles(out,file,path);
        }
        else if(file.exists()){
            response=showContent(out,file);
        }
        else{
            response=sendErrorResponse(out,404,"Not Found");
            System.out.println("Not found. HTTP 404 error");
        }
        logResponse(requestLine,response);
    }
    private String sendErrorResponse(OutputStream out, int statusCode, String statusMessage) throws IOException {
        String response = "HTTP/1.0 " + statusCode + " " + statusMessage + "\r\n\r\n";
        out.write(response.getBytes());
        return response;
    }
    private String showContent(OutputStream out, File file) throws IOException {
        String contentType = getContentType(file);
        String response = "";

        response = "HTTP/1.0 200 OK\r\n" + "Content-Type: " + contentType + "\r\n";

        if (contentType.startsWith("text/") || contentType.startsWith("image/")) {
            response += "\r\n";
            out.write(response.getBytes());

            try (FileInputStream fileIn = new FileInputStream(file)) {
                byte[] buffer = new byte[CHUNK_SIZE];
                int bytesRead;
                while ((bytesRead = fileIn.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                }
            }
        } else {
            response += "Content-Disposition: attachment; filename=\"" + file.getName() + "\"\r\n\r\n";
            out.write(response.getBytes());
            try (FileInputStream fileIn = new FileInputStream(file)) {
                byte[] buffer = new byte[CHUNK_SIZE];
                int bytesRead;
                while ((bytesRead = fileIn.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                }
            }
        }
        return response;
    }


    private String getContentType(File file) {
        String type=file.getName().toLowerCase();
        if(type.endsWith(".txt"))
            return "text/plain";
        else if(type.endsWith(".jpg")||type.endsWith(".jpeg"))
            return "image/jpeg";
        else if(type.endsWith(".png"))
            return "image/png";
        else {
            return "application/octet-stream";
        }
    }

    private String showListOfFiles(OutputStream out, File file,String currentPath) throws IOException {
        String response="";
        response=response+"HTTP/1.0 OK\r\n"+"Content-Type: text/html\r\n\r\n";
        response=response+"<html><body><h1> All files in "+file.getName()+"</h1><ul>";
        for(File f: Objects.requireNonNull(file.listFiles())){
            String filePath = currentPath + (currentPath.endsWith("/") ? "" : "/") + f.getName();
            if (f.isDirectory()) {
                response+="<li>" +
                                "<a href=\""+filePath+"\">" +
                                "<b><i>"+ f.getName()+"</i></b></a>" +
                           "</li>";
            } else {
                response+="<li>" +
                                "<a href=\""+filePath+"\">"+
                                f.getName()+"</a>" +
                          "</li>";
            }
        }
        response+="</ul></body></html>";
        out.write(response.getBytes());
        return response;
    }
    private void logResponse(String request, String response) {
        try (PrintWriter log = new PrintWriter(new FileWriter("server.log", true))) {
            requestCount+=1;
            log.println(requestCount+".\n");
            log.println("Request: " + request);
            log.println("Response: " + response);
        } catch (IOException e) {
            System.out.println("Logging exception: " + e.getMessage());
        }
    }

}
