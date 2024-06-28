package obliczenia;

public abstract class Operator2arg extends Operator1arg {

    protected final Wyrazenie wyrazenie2;

    protected Operator2arg(Wyrazenie wyrazenie1, Wyrazenie wyrazenie2) {
        super(wyrazenie1);
        if (wyrazenie2 == null) throw new IllegalArgumentException("Brak wyrazenia");
        this.wyrazenie2 = wyrazenie2;
    }
}
