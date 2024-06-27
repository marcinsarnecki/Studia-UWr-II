import java.util.Arrays;

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

        int[] arr = new int[100];
        for (int i = 0; i < 100; i++)
            arr[i] = (-50 + i * 76) % 123;
        int[] tmp = new int[100];
        AtomicCounter atomicCounter = new AtomicCounter(8);
        MergeSort mergeSort = new MergeSort(arr, tmp, 0, arr.length - 1, atomicCounter);
        Thread t = new Thread(mergeSort);
        t.start();
        try {
            t.join();
            System.out.println(Arrays.toString(arr));
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }
}