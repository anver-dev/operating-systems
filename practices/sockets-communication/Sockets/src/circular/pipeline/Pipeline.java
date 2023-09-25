package circular.pipeline;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Pipeline {
    private static ServerSocket serverSocket;
    private static String HOSTNAME = "localhost";
    private static int BASE_PORT = 4000;
    private static int ID_PIPELINE;


    public static void main(String[] args) throws InterruptedException {
        ID_PIPELINE = Integer.parseInt(args[0]);
        int totalProcess = Integer.parseInt(args[1]);
        int message = generateRandomValue();
        int messageToSend = message;
        int suma = 0;

        int port = BASE_PORT + ID_PIPELINE;

        try {
            serverSocket = new ServerSocket(port);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        Thread.sleep(5000);
        System.out.println("Soy el proceso :: " + ID_PIPELINE + " con el mensaje inicial :: " + message);

        for (int i = 0; i < totalProcess - 1; i++) {
            int nextPort = BASE_PORT + ((ID_PIPELINE + 1) % totalProcess);
            try {
                enviar(messageToSend, nextPort);
                int received = recibir();
                suma = suma + received;
                messageToSend = received;
            } catch (IOException e) {
                System.out.println("No se pudo conectar con el cliente");
            }
        }

        System.out.println("Soy el proceso :: " + ID_PIPELINE + " con el mensaje final :: " + (suma + message));
    }

    private static int generateRandomValue() {
        return (int) (Math.random() * 10 + 1);
    }

    private static int recibir() {
        try {
            Socket clienteSocket = serverSocket.accept();

            BufferedReader entrada = new BufferedReader(new InputStreamReader(clienteSocket.getInputStream()));
            String mensajeCliente = entrada.readLine();

            clienteSocket.close();

            return Integer.parseInt(mensajeCliente);
        } catch (IOException e) {
            System.out.println("Error " + e.getMessage());
            return 0;
        }
    }

    public static void enviar(int message, int nextProcess) throws IOException {
        Socket socket = new Socket(HOSTNAME, nextProcess);

        PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
        output.println(message);

    }
}
