package semaphore;

import java.util.concurrent.atomic.AtomicInteger;

class Addition implements Runnable {
    static final int N = 200000;
    private final String name;
    private final CustomSemaphore semaphore;
    private final AtomicInteger atomicSum;

    public Addition(CustomSemaphore semaphore, String name, AtomicInteger atomicSum) {
        this.name = name;
        this.semaphore = semaphore;
        this.atomicSum = atomicSum;
    }

    public void run() {
        System.out.println("Hilo: " + name);

        for (int i = 0; i < N; i++) {
            semaphore.acquire(); // Adquirir un permiso
            atomicSum.incrementAndGet(); // Incrementar la suma atómicamente
            semaphore.release(); // Liberar el permiso
        }
    }
} 
