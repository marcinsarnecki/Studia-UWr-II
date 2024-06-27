import java.util.Arrays;

class MergeSort implements Runnable {
    protected int[] arr;
    protected int[] temp;
    protected int l, r;

    MergeSort(int[] arr, int[] temp, int l, int r) {
        this.arr = arr;
        this.temp = temp;
        this.l = l;
        this.r = r;
    }

    private void merge(int l, int m, int r) {// 1.2 usuwamy synchronized bo nie potrzeba
        int n1 = m - l + 1;
        int n2 = r - m;
//        int[] left = new int[n1];
//        int[] right = new int[n2];
        System.arraycopy(arr, l, temp, l, n1);
        System.arraycopy(arr, m + 1, temp, m + 1, n2);
        int i = 0, j = 0;
        int k = l;
        while (i < n1 && j < n2)
            if (temp[l + i] < temp[m + 1 + j])
                arr[k++] = temp[l + i++];
            else
                arr[k++] = temp[m + 1 + j++];
        while (i < n1)
            arr[k++] = temp[l + i++];
        while (j < n2)
            arr[k++] = temp[m + 1 + j++];
    }

    public void sort(int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            sort(l, m);
            sort(m + 1, r);
            merge(l, m, r);
        }
    }

    @Override
    public void run() {
        if (this.l < this.r) {
            int m = (this.l + this.r) / 2;
            MergeSort left = new MergeSort(arr, temp, this.l, m);
            MergeSort right = new MergeSort(arr, temp, m + 1, this.r);
            Thread t1 = new Thread(left);
            Thread t2 = new Thread(right);
            t1.start();
            t2.start();
            try {
                t1.join();
                t2.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            this.merge(this.l, m, this.r);
        }
    }
}

