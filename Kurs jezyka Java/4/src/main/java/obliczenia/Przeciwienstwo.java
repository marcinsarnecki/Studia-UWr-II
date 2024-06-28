package obliczenia;

public class Przeciwienstwo extends Operator1arg {
    protected Przeciwienstwo(Wyrazenie wyrazenie1) {
        super(wyrazenie1);
    }

    @Override
    public double oblicz() {
        return -this.wyrazenie1.oblicz();
    }

    @Override
    public String toString() {
        return "-( " + this.wyrazenie1 + " )";
    }
}
