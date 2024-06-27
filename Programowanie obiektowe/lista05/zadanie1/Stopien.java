public interface Stopien extends Comparable<Stopien>{
    int get_value();
    @Override int compareTo(Stopien toCompare);
    public String get_name();//dodatkowo definiuje tutaj funkcje do zwrocenia nazwy
}