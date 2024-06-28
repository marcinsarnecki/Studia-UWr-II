package obliczenia;

public abstract class Operator1arg extends Dzialanie {
    protected final Wyrazenie wyrazenie1;

    protected Operator1arg(Wyrazenie wyrazenie1) {
        if (wyrazenie1 == null) throw new IllegalArgumentException("Brak wyrazenia");
        this.wyrazenie1 = wyrazenie1;
    }
}
