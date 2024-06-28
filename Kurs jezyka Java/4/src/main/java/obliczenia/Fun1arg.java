package obliczenia;

public abstract class Fun1arg extends Dzialanie {
    protected final Wyrazenie wyrazenie1;

    protected Fun1arg(Wyrazenie wyrazenie1) {
        if (wyrazenie1 == null) throw new IllegalArgumentException("Brak wyrazenia");
        this.wyrazenie1 = wyrazenie1;
    }
}