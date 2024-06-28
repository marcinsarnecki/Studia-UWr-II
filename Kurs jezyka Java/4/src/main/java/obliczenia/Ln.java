package obliczenia;

public class Ln extends Fun1arg{
    protected Ln(Wyrazenie wyrazenie1) {
        super(wyrazenie1);
    }

    @Override
    public double oblicz() {
        return Math.log(this.wyrazenie1.oblicz());
    }

    @Override
    public String toString() {
        return "ln( " + wyrazenie1 + " )";
    }
}