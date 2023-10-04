package semaphore;

import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.LockSupport;

public class CustomSemaphore {
    private final AtomicInteger permits;
    private final ConcurrentLinkedQueue<Thread> queue;

    public CustomSemaphore(int permits) {
        if (permits < 1) {
            throw new IllegalArgumentException("Permits must be greater than or equal to 1");
        }
        this.permits = new AtomicInteger(permits);
        this.queue = new ConcurrentLinkedQueue<>();
    }

    public void acquire() {
        while (true) {
            Thread currentThread = Thread.currentThread();

            if (permits.get() > 0 && (queue.isEmpty() || queue.peek() == currentThread)) {
                    permits.decrementAndGet();
                    queue.remove(currentThread);
                    return;
            }

            queue.add(currentThread);
            LockSupport.park();
        }
    }

    public void release() {
        permits.incrementAndGet();

        if (!queue.isEmpty()) {
            LockSupport.unpark(queue.peek());
        }
    }
}
