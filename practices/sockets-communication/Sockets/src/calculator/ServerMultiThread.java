package calculator;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import static calculator.Utils.getResultOfOperationByType;

public class ServerMultiThread implements Runnable {
    private Socket socket;
    static List<String> clientsConnected = new ArrayList<>();

    @Override
    public void run() {
        try {
            ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
            ObjectInputStream input = new ObjectInputStream(socket.getInputStream());

            ClientMessage clientMessage = (ClientMessage) input.readObject();

            if (clientIsLogged(clientMessage.getNickname())) {
                ServerMessage errorMessage = new ServerMessage();

                errorMessage.setResponse("ERROR: Ya existe un cliente con el nickname ingresado, intenta nuevamente.");
                output.writeObject(errorMessage);
            } else {
                clientsConnected.add(clientMessage.getNickname());

                ServerMessage serverMessage = new ServerMessage();

                serverMessage.setResponse("Ingrese la operación a realizar.");
                output.writeObject(serverMessage);

                clientMessage = (ClientMessage) input.readObject();

                System.out.println("Realizando operación :: " + clientMessage.getOperationType());
                ServerMessage resultMessage = new ServerMessage();

                try {
                    resultMessage.setResponse(getResponseWithFormat(clientMessage));

                    clientsConnected.remove(clientMessage.getNickname());

                    output.writeObject(resultMessage);
                } catch (RuntimeException e) {
                    ServerMessage errorMessage = new ServerMessage();

                    errorMessage.setResponse(e.getMessage());
                    output.writeObject(errorMessage);
                }
            }

            socket.close();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    private String getResponseWithFormat(ClientMessage clientMessage) {
        String template = clientMessage.getNickname() + " : ";

        try {
            double result = getResultOfOperationByType(clientMessage.getOperationType(), clientMessage.getNumbers());
            return template + result;
        } catch (RuntimeException e) {
            return template + e.getMessage();
        }
    }

    private boolean clientIsLogged(String nickname) {
        return clientsConnected.contains(nickname);
    }

    public ServerMultiThread(Socket socket) {
        this.socket = socket;
    }

    public ServerMultiThread() {
        initServer();
    }

    public void initServer() {
        int PORT = 8080;
        ServerSocket serverSocket;
        Socket socketInitial;

        try {
            serverSocket = new ServerSocket(PORT);
            while (true) {
                System.out.println("Esperando conexión en el puerto :: " + PORT);

                socketInitial = serverSocket.accept();

                ServerMultiThread serverThread = new ServerMultiThread(socketInitial);
                Thread clientThread = new Thread(serverThread);

                clientThread.start();

                System.out.println("Cliente conectado.");
                System.out.println("Usuarios conectados :: ");
                clientsConnected.forEach(System.out::println);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        new ServerMultiThread();
    }
}
