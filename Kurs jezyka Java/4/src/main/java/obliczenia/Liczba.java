package obliczenia;

public class Liczba extends Operand {
    public Liczba(double wartosc) {
        this.wartosc = wartosc;
    }

    @Override
    public double oblicz() {
        return this.wartosc;
    }

    @Override
    public String toString() {
        return String.valueOf(wartosc);
    }
}
