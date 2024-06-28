package obliczenia;

public class Odwrotnosc extends Operator1arg {
    protected Odwrotnosc(Wyrazenie wyrazenie1) {
        super(wyrazenie1);
    }

    @Override
    public double oblicz() {
        return 1.0 / this.wyrazenie1.oblicz();
    }

    @Override
    public String toString() {
        return "1 / ( " + this.wyrazenie1 + " )";
    }
}