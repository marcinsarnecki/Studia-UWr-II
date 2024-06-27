import java.util.Hashtable;

class Leaf implements Expression {
    int value;
    @Override public int Evaluate() {
        return value;
    }
    @Override public String toString() {
        return String.valueOf(value);
    }
    public Leaf(int x) {
        value = x;
    }
}

class Variable implements Expression {
    String var;
    static Hashtable<String,Integer> mapa = new Hashtable<String,Integer>();
    public Variable(String name)
    {
        this.var = name;
    }
    public int Evaluate()
    {
        return mapa.get(var);
    }
    public String toString()
    {
        return var;
    }
}

class Vertice implements Expression {
    int operation;// 0 1 2 3 // + - * / 
    Expression left, right;
    @Override public int Evaluate() {
        switch(operation) {
            case 0: 
                return left.Evaluate() + right.Evaluate();
            case 1:
                return left.Evaluate() - right.Evaluate();
            case 2:
                return left.Evaluate() * right.Evaluate();
            case 3:
                return left.Evaluate() / right.Evaluate();
            default:
                return 0;
        }
    }
    @Override public String toString() {
        switch(operation) {
            case 0: 
                return "(" + left.toString() + " + " + right.toString() + ")";
            case 1:
                return "(" + left.toString() + " - " + right.toString() + ")";
            case 2:
                return "(" + left.toString() + " * " + right.toString() + ")"; 
            case 3:
                return "(" + left.toString() + " / " + right.toString() + ")";
            default:
                return "";
        } 
    }
    public Vertice(int a, Expression l, Expression r) {
        operation = a;
        left = l;
        right = r;
    }
}