package obliczenia;

public abstract class Fun2arg extends Fun1arg{
    protected final Wyrazenie wyrazenie2;

    protected Fun2arg(Wyrazenie wyrazenie1, Wyrazenie wyrazenie2) {
        super(wyrazenie1);
        if (wyrazenie2 == null) throw new IllegalArgumentException("Brak wyrazenia");
        this.wyrazenie2 = wyrazenie2;
    }
}
