public class B implements litera{
    @Override public int get_value() {
        return 2;
    }
    @Override public int compareTo(litera toCompare) {
        return Integer.compare(this.get_value(), toCompare.get_value());
    }
    @Override public String get_name() {
        return "B";
    }
}