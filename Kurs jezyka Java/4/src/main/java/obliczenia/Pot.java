package obliczenia;

public class Pot extends Fun2arg{
    public Pot(Wyrazenie wyrazenie1, Wyrazenie wyrazenie2) {
        super(wyrazenie1, wyrazenie2);
    }

    @Override
    public double oblicz() {
        return Math.pow(wyrazenie1.oblicz(), wyrazenie2.oblicz());
    }

    @Override
    public String toString() {
        return "(" + wyrazenie1 + " do potegi " + wyrazenie2 + ")";
    }
}