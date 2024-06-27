public class mergesort implements Runnable {
    litera array[];
    int begin, end;
    public mergesort(litera[] tab, int a, int b) {
        array = tab;
        begin = a;
        end = b;
    }
    private void InsertionSort() {
        for (int i = begin + 1; i <= end; i++)
        {
            int j;
            litera pom = array[i];
            for (j = i - 1; j >= begin; j--) {
                if (array[j].compareTo(pom) <= 0) // <= 
                    break;
                array[j + 1] = array[j];
            }
            array[j + 1] = pom;
        }
    }
    private void Merge() {
        int k = (begin + end) / 2;
        litera[] temp = new litera[end+1];
        int i1 = begin, i2 = k + 1, t1 = 0;
        while(i1 <= k && i2 <= end) {
            if(array[i1].compareTo(array[i2]) == -1 )// < 
                temp[t1++] = array[i1++];
            else
                temp[t1++] = array[i2++];
        }
        while (i1 <= k) 
            temp[t1++] = array[i1++];
        while (i2 <= end) 
            temp[t1++] = array[i2++];
        System.arraycopy(temp, 0,array, begin, end - begin + 1);
    }

    public void run() {
        if(end - begin < 6) {//jak tablica jest mala to lepiej proste wstawianie niz rekurencyjny merge
            InsertionSort();
            return;
        }
        int k = (begin + end) / 2;
        mergesort left = new mergesort(array, begin, k);
        mergesort right = new mergesort(array, k + 1, end); 

        Thread thread_left  = new Thread(left);
        Thread thread_right = new Thread(right);

        thread_left.start();
        thread_right.start();

        try {thread_left.join();}
        catch (InterruptedException e) {e.printStackTrace();}

        try {thread_right.join();}
        catch (InterruptedException e) {e.printStackTrace();}

        Merge();
    }
    public void print() {
        for(int i = 0; i <= end; i++)
            System.out.println(array[i].get_name());
    }
}
