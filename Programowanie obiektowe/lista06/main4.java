public class main4 {
    public static void main(String[] args) {
        litera[] tab = new litera[10];
        tab[0] = new A();
        tab[1] = new C();
        tab[2] = new B();
        tab[3] = new C();
        tab[4] = new A();
        tab[5] = new A();
        tab[6] = new C();
        tab[7] = new C();
        tab[8] = new B();
        tab[9] = new B();
        mergesort m = new mergesort(tab, 0, tab.length-1);//sortuje literki 
        Thread thread = new Thread(m);
        thread.start();
        try {thread.join();}
        catch (InterruptedException e) {e.printStackTrace();}
        m.print();
    }
}