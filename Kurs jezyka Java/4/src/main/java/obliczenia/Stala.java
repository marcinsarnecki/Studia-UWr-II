package obliczenia;

public abstract class Stala extends Operand {
    @Override
    public double oblicz() {
        return this.wartosc;
    }
}
