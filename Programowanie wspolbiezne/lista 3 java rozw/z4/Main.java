import java.util.Arrays;
import java.util.Random;
//public class Main {
//    public static void main(String[] args) {
//        int arr[] = {4, 3, 2, 1};
//        MergeSort w = new MergeSort(arr, 0, 3);
//
//        Thread t = new Thread(w);
//
//        t.start();
//        try {
//            t.join();
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//
//        for (int i = 0; i < 4; i++)
//            System.out.printf("%d ", arr[i]);
//        System.out.println("Hello world!");
//    }
//}

class Main {
    public static void main(String[] args) {
        Random rand = new Random();
        int[] arr = new int[1000];
        for (int i = 0; i < 1000; i++)
            arr[i] = rand.nextInt(2);
        AtomicCounter atomicCounter = new AtomicCounter(8);
        var subsequence = new Subsequence(arr, atomicCounter, 0, arr.length - 1);
        Thread t = new Thread(subsequence);
        t.start();
        try {
            t.join();
            System.out.println(subsequence.result);
            System.out.println(Arrays.toString(arr));
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}