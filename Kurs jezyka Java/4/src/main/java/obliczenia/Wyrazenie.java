package obliczenia;

public abstract class Wyrazenie implements Obliczalny {
    public static double suma(Wyrazenie... wyr) {
        double suma = 0;
        for (int i = 0; i < wyr.length; i++) {
            suma += wyr[i].oblicz();
        }
        return suma;
    }

    public static double iloczyn(Wyrazenie... wyr) {
        double iloczyn = 1;
        for (int i = 0; i < wyr.length; i++) {
            iloczyn *= wyr[i].oblicz();
        }
        return iloczyn;
    }
}
