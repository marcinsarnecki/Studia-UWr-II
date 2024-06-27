public class Main1 {
    public static void main (String[] args)
    {
        KolekcjaStopni stopnie = new KolekcjaStopni();
        
        stopnie.AddElement(new Szeregowy());
        stopnie.AddElement(new Kapral());
        stopnie.AddElement(new Chorazy());
        stopnie.AddElement(new Pulkownik());

        String s = stopnie.toString();
        System.out.print("Wyswietlam cala liste: \n" + s);

        System.out.print("Dodaje nowe elementy!\n");

        stopnie.AddElement(new Chorazy());
        stopnie.AddElement(new Pulkownik());
        stopnie.AddElement(new Szeregowy());
        stopnie.AddElement(new Kapral());
        stopnie.AddElement(new Kapral());
        stopnie.AddElement(new Kapral());

        s = stopnie.toString();
        System.out.print("Wyswietlam cala liste: \n" + s);

        System.out.print("Wyciagam pierwsze 3 elementy\n");
        Stopien temp = stopnie.get_first();
        System.out.println(temp.get_name());
        temp = stopnie.get_first();
        System.out.println(temp.get_name());
        temp = stopnie.get_first();
        System.out.println(temp.get_name());
    }
}
