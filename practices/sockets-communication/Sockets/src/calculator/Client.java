package calculator;

import java.io.*;
import java.net.Socket;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

import static calculator.Utils.*;

public class Client {
    private static final String HOSTNAME = "localhost";
    private static final int PORT = 8080;
    private static final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        Socket socket = new Socket(HOSTNAME, PORT);
        System.out.println("Cliente conectado en :: " + HOSTNAME + ":" + PORT);

        ClientMessage message = new ClientMessage();
        String nickname = readNickname();

        message.setNickname(nickname);

        ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream input = new ObjectInputStream(socket.getInputStream());

        output.writeObject(message);

        ServerMessage returnMessage = (ServerMessage) input.readObject();

        if (returnMessage.getResponse().contains("ERROR")) {
            System.out.println(returnMessage.getResponse());
        } else {
            message = getOperationFromUser();
            message.setNickname(nickname);

            output.writeObject(message);

            ServerMessage result = (ServerMessage) input.readObject();
            System.out.println("RESULT: \n" + result.getResponse());
        }

        output.close();
        socket.close();
    }

    private static ClientMessage getOperationFromUser() throws IOException {
        ClientMessage clientMessage = new ClientMessage();
        List<Double> numbers;
        String operation;

        switch (getMenuChoice()) {
            case 1 -> {
                System.out.println("Ingresa la suma:");

                operation = reader.readLine();
                numbers = getNumbers(operation, "+");
                clientMessage.setNumbers(numbers);
                clientMessage.setOperationType(SUMA);
            }
            case 2 -> {
                System.out.println("Ingresa la resta:");

                operation = reader.readLine();
                numbers = getNumbers(operation, "-");
                clientMessage.setNumbers(numbers);
                clientMessage.setOperationType(RESTA);
            }
            case 3 -> {
                System.out.println("Ingresa la multiplicación:");

                operation = reader.readLine();
                numbers = getNumbers(operation, "*");
                clientMessage.setNumbers(numbers);
                clientMessage.setOperationType(MULTIPLICACION);
            }
            case 4 -> {
                System.out.println("Ingresa la división:");

                operation = reader.readLine();
                numbers = getNumbers(operation, "/");
                clientMessage.setNumbers(numbers);
                clientMessage.setOperationType(DIVISION);

            }

            default -> System.out.println("Ingresa una opción válida.");
        }

        return clientMessage;
    }

    private static List<Double> getNumbers(String operation, String operationTypeSymbol) {
        String operationRegex = "[" + operationTypeSymbol + "]";
        return Arrays.stream(operation.split(operationRegex)).map(Double::valueOf).collect(Collectors.toList());
    }

    public static int getMenuChoice() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("-------------------------");
        System.out.println("1 - SUMA");
        System.out.println("2 - RESTA");
        System.out.println("3 - MULTIPLICACIÓN");
        System.out.println("4 - DIVISIÓN");

        return scanner.nextInt();
    }

    private static String readNickname() throws IOException {
        System.out.println("Ingresa un nickname");
        return reader.readLine();
    }
}
