import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class KolekcjaStopni {
    List<Stopien> lista;

    KolekcjaStopni() {
        lista = new ArrayList<Stopien>();
    }

    void AddElement(Stopien toAdd) {
        lista.add(toAdd);
        Collections.sort(lista);
    }

    Stopien get_first() {
        if(lista.size() == 0) {
            System.out.println("Lista jest pusta!\n");
            return null;
        }
        Stopien temp = lista.get(0);
        lista.remove(0);
        return temp;
    }
    @Override public String toString() {
        String ans = new String("");
        for(Stopien it: lista) {
            ans = ans + it.get_name();
            ans = ans + "\n";
        }
        return ans;
    }
}
