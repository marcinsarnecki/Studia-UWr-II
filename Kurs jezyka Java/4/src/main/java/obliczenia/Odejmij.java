package obliczenia;

public class Odejmij extends Operator2arg{
    public Odejmij(Wyrazenie wyrazenie1, Wyrazenie wyrazenie2) {
        super(wyrazenie1, wyrazenie2);
    }
    @Override
    public double oblicz() {
        return wyrazenie1.oblicz() - wyrazenie2.oblicz();
    }

    @Override
    public String toString() {
        return "( " + wyrazenie1 + " - " + wyrazenie2.toString() + " )";
    }
}
