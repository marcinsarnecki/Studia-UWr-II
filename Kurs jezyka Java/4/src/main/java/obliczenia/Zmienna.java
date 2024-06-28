package obliczenia;

import struktury.ZbiorTablicowy;
import struktury.Para;
public class Zmienna extends Operand {
    public static final ZbiorTablicowy zbiorTablicowy = new ZbiorTablicowy(50);

    public Zmienna(String klucz) {
        this.wartosc = zbiorTablicowy.szukaj(klucz).getWartosc();
    }

    @Override
    public double oblicz() {
        return this.wartosc;
    }

    @Override
    public String toString() {
        return String.valueOf(this.wartosc);
    }
}
