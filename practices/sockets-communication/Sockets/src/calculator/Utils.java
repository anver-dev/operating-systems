package calculator;

import java.util.List;

public class Utils {
    public static final String SUMA = "suma";
    public static final String RESTA = "resta";
    public static final String MULTIPLICACION = "multiplicacion";
    public static final String DIVISION = "division";

    public static double getResultOfOperationByType(String operationType, List<Double> numbers) {
        if (operationType.equalsIgnoreCase(SUMA)) {
            return calculateSuma(numbers);
        }

        if (operationType.equalsIgnoreCase(RESTA)) {
            return calculateResta(numbers);
        }

        if (operationType.equalsIgnoreCase(MULTIPLICACION)) {
            return calculateMultiplication(numbers);
        }

        if (operationType.equalsIgnoreCase(DIVISION)) {
            return calculateDivision(numbers);
        }
        return 0;
    }

    private static double calculateDivision(List<Double> numbers) {
        if (numbers.size() > 2) {
            throw new RuntimeException("Solo se pueden dividir dos numeros");
        }

        if (numbers.get(1) == 0) {
            throw new RuntimeException("No se puede dividir entre cero");
        }

        return (double) numbers.get(0) / numbers.get(1);
    }

    private static double calculateMultiplication(List<Double> numbers) {
        double result = 1;

        for (Double number : numbers) {
            result = result * number;
        }

        return result;
    }

    private static double calculateResta(List<Double> numbers) {
        double result = 0;

        for (Double number : numbers) {
            result = result - number;
        }
        return result;
    }

    private static double calculateSuma(List<Double> numbers) {
        double result = 0;

        for (Double number : numbers) {
            result = result + number;
        }
        return result;
    }
}
