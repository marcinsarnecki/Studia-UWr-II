package obliczenia;

public class Cos extends Fun1arg {
    protected Cos(Wyrazenie wyrazenie1) {
        super(wyrazenie1);
    }

    @Override
    public double oblicz() {
        return Math.cos(this.wyrazenie1.oblicz());
    }

    @Override
    public String toString() {
        return "cos( " + wyrazenie1 + " )";
    }
}
