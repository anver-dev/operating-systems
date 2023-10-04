package semaphore;

import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    static final int MAX_THREADS = 4;

    public static void main(String[] args) throws InterruptedException {
        CustomSemaphore semaphore = new CustomSemaphore(3); // Número máximo de hilos permitidos al mismo tiempo
        // Utiliza una variable atómica para la suma
        AtomicInteger suma = new AtomicInteger(0);

        Thread[] t = new Thread[MAX_THREADS];

        for (int i = 0; i < MAX_THREADS; i++) {
            t[i] = new Thread(new Addition(semaphore, "T" + i, suma));
            t[i].start();
        }

        for (int i = 0; i < MAX_THREADS; i++) {
            t[i].join(); // Esperar a que todos los hilos terminen
        }

        System.out.println("Resultado final:" + suma.get());
    }
} 
