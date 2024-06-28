package struktury;

import java.util.Objects;

public class Para implements Cloneable, Comparable<Para> {
    public final String klucz;
    private double wartosc;

    public Para(String klucz, double wartosc) {
        if (klucz == null || !klucz.matches("[a-z]+")) {
            throw new IllegalArgumentException("Klucz nie moze byc nullem oraz musi skladac sie z malych liter alfabetu angielskiego");
        }
        this.klucz = klucz;
        this.wartosc = wartosc;
    }

    public double getWartosc() {
        return wartosc;
    }

    public void setWartosc(double wartosc) {
        this.wartosc = wartosc;
    }


    @Override
    public String toString() {
        return "Para{" +
                "klucz='" + klucz + '\'' +
                ", wartosc=" + wartosc +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Para para)) return false;
        return Objects.equals(klucz, para.klucz);
    }

    @Override
    public int compareTo(Para p) {
        return Double.compare(this.wartosc, p.wartosc);
    }

    @Override
    public Para clone() {
        try {
            Para clone = (Para) super.clone();
            return clone;
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }
}
