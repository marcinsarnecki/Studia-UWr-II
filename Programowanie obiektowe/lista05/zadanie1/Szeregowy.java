public class Szeregowy implements Stopien{
    @Override public int get_value() {
        return 50;
    }
    @Override public int compareTo(Stopien toCompare) {
        return Integer.compare(this.get_value(), toCompare.get_value());
    }
    @Override public String get_name() {
        return "Szeregowy";
    }
}
