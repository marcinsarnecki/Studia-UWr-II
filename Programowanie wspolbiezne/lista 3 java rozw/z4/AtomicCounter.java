public class AtomicCounter {
    private int counter = 0;
    private final int M;


    public synchronized boolean checkAndIncrement() {
        if (counter < M) {
            counter++;
            return true;
        }
        return false;
    }

    public synchronized void decrement() {
        counter--;
    }
    public AtomicCounter(int m) {
        M = m - 1;
    }
}
