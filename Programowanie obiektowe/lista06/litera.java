public interface litera extends Comparable<litera>{
    int get_value();
    @Override int compareTo(litera toCompare);
    public String get_name();
}