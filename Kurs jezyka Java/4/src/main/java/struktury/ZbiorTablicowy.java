package struktury;

import java.util.Arrays;

public class ZbiorTablicowy implements Zbior, Cloneable {
    private Para[] zbior;
    private int zapelnienie;

    public ZbiorTablicowy(int rozmiar) {
        this.zbior = new Para[rozmiar];
        this.zapelnienie = 0;
    }

    @Override
    public Para szukaj(String k) {
        for (Para para : zbior) {
            if (para != null && para.klucz.equals(k)) {
                return para;
            }
        }
        return null;
    }

    @Override
    public void wstaw(Para p) {
        if (zapelnienie == zbior.length) {
            throw new IllegalStateException("Zbior jest calkowicie zapelniony.");
        }
        for (int i = 0; i < zapelnienie; i++) {
            if (zbior[i].klucz.equals(p.klucz)) {
                zbior[i] = p;
                return;
            }
        }
        zbior[zapelnienie++] = p;
    }
    @Override
    public void usun(String k) {
        for (int i = 0; i < zapelnienie; i++) {
            if (zbior[i] != null && zbior[i].klucz.equals(k)) {
                zbior[i] = null;
                for (int j = i; j < zapelnienie - 1; j++) {
                    zbior[j] = zbior[j + 1];
                }
                zapelnienie--;
                return;
            }
        }
    }
    @Override
    public void czysc() {
        Arrays.fill(zbior, null);
        zapelnienie = 0;
    }
    @Override
    public int ile() {
        return zapelnienie;
    }
    @Override
    public ZbiorTablicowy clone() {
        try {
            ZbiorTablicowy cloned = (ZbiorTablicowy) super.clone();
            cloned.zbior = Arrays.copyOf(this.zbior, this.zbior.length);
            return cloned;
        } catch (CloneNotSupportedException e) {
            throw new InternalError(e);
        }
    }
}