public class A implements litera{
    @Override public int get_value() {
        return 1;
    }
    @Override public int compareTo(litera toCompare) {
        return Integer.compare(this.get_value(), toCompare.get_value());
    }
    @Override public String get_name() {
        return "A";
    }
}