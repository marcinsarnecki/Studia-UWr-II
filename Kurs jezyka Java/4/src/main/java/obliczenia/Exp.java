package obliczenia;

public class Exp extends Fun1arg{
    protected Exp(Wyrazenie wyrazenie1) {
        super(wyrazenie1);
    }

    @Override
    public double oblicz() {
        return Math.exp(this.wyrazenie1.oblicz());
    }

    @Override
    public String toString() {
        return "e do potegi ( " + wyrazenie1 + " )";
    }
}
