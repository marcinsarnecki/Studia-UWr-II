package obliczenia;

public class Sin extends Fun1arg {
    protected Sin(Wyrazenie wyrazenie1) {
        super(wyrazenie1);
    }

    @Override
    public double oblicz() {
        return Math.sin(this.wyrazenie1.oblicz());
    }

    @Override
    public String toString() {
        return "sin( " + wyrazenie1 + " )";
    }
}
