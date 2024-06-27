import java.util.Hashtable;

public class Main2
{
    public static void main(String[] args)
    {
        Hashtable<String, Integer> m = new Hashtable<String, Integer>();//mapa
        m.put("+", 0);
        m.put("-", 1);
        m.put("*", 2);
        m.put("/", 3);

        Vertice dodaj = new Vertice(m.get("+"), new Leaf(8), new Leaf(2));      //dodawanie
        System.out.println(dodaj.toString() + " = " + dodaj.Evaluate());

        Vertice odejmij = new Vertice(m.get("-"), new Leaf(8), new Leaf(2));    //odejmowanie
        System.out.println(odejmij.toString() + " = " + odejmij.Evaluate());

        Vertice pomnoz = new Vertice(m.get("*"), new Leaf(8), new Leaf(2));     //mnozenie
        System.out.println(pomnoz.toString() + " = " + pomnoz.Evaluate());

        Vertice podziel = new Vertice(m.get("/"), new Leaf(8), new Leaf(2));    //dzielenie
        System.out.println(podziel.toString() + " = " + podziel.Evaluate());

        Vertice root = new Vertice(m.get("-"),              //
                            new Vertice(m.get("*"),         //                      drzewo
                                new Vertice(m.get("*"),     //
                                    new Leaf(3),            //                       28
                                    new Leaf(2)),           //                30     (-)     2
                                new Leaf(5)),               //             6  (*)  5      4 (/) 2
                            new Vertice(m.get("/"),         //          3 (*) 2
                                new Leaf(4), 
                                new Leaf(2)));
        System.out.println(root.toString() + " = " + root.Evaluate());

        Variable x = new Variable("x");
        Variable y = new Variable("y");
        Variable z = new Variable("z");
        Variable.mapa.put("x", 2);
        Variable.mapa.put("y", 3);
        Variable.mapa.put("z", 4);

        Vertice root2 = new Vertice(m.get("+"), x, new Vertice(m.get("*"), y, z));
        System.out.println(root2.toString() + " = " + root2.Evaluate());
    }
}