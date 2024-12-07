package Uploader;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Client {
    public static String serverAddress="localhost";
    public static final int serverPort=5042;
    public static Boolean isValid(File file){
        String fileName = file.getName().toLowerCase();
        return fileName.endsWith(".txt")
                || fileName.endsWith(".jpg")
                || fileName.endsWith(".png")
                || fileName.endsWith(".mp4");
    }

    public static void main(String[] args) {
        Scanner scn=new Scanner(System.in);
        String uploadPath="upload_files/";
        try{
            while (true){
                String requestLine=scn.nextLine();
                String[] tokens=requestLine.split(" ");
                if(!tokens[0].equalsIgnoreCase("UPLOAD") || tokens.length!=2){
                    System.out.println("Invalid command");
                    continue;
                }
                String fileName=tokens[1];
                String filePath=uploadPath+fileName;
                File file=new File(filePath);
                if(file.exists() && file.isFile() && !file.isDirectory() && isValid(file)){
                    Thread handleUploadFIle=new HandleUploadFile(file);
                    handleUploadFIle.start();
                }
                else {
                    System.out.println("Sorry Invalid file name or format");
                }
            }
        }catch (Exception e){
            System.out.println("Uploader client exception: "+e);
        }
    }
}
