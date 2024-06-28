package obliczenia;

public class Log extends Fun2arg{
    public Log(Wyrazenie wyrazenie1, Wyrazenie wyrazenie2) {
        super(wyrazenie1, wyrazenie2);
    }

    @Override
    public double oblicz() {
        return Math.log(wyrazenie2.oblicz()) / Math.log(wyrazenie1.oblicz());
    }

    @Override
    public String toString() {
        return "logarytm z ( " + wyrazenie1 + " ) o podstawie (" + wyrazenie2 + ")";
    }
}
