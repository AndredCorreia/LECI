package aula06;

import java.util.HashSet;

class Conjunto {
    private HashSet<Integer> conjunto;

    public Conjunto() {
        conjunto = new HashSet<>();
    }

    public void insert(int n) {
            conjunto.add(n); 
    
    }

    public boolean contains(int n) {
        return conjunto.contains(n);
    }

    public void remove(int n) {
        conjunto.remove(n);
    }

    public void empty() {
        conjunto.clear();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int el : conjunto) {
            sb.append(el).append(" ");
        }
        return sb.toString().trim();
    }

    public int size() {
        return conjunto.size();
    }

    public Conjunto combine(Conjunto add) {
        Conjunto result = new Conjunto();
        result.conjunto.addAll(this.conjunto);
        result.conjunto.addAll(add.conjunto);
        return result;
    }

    public Conjunto subtract(Conjunto dif) {
        Conjunto result = new Conjunto();
        result.conjunto.addAll(this.conjunto);
        result.conjunto.removeAll(dif.conjunto);
        return result;
    }

    public Conjunto intersect(Conjunto inter) {
        Conjunto result = new Conjunto();
        result.conjunto.addAll(this.conjunto);
        result.conjunto.retainAll(inter.conjunto); 
        return result;
    }
    
    public Conjunto unir(Conjunto add) {
        return this.combine(add);
    }

    public Conjunto interset(Conjunto inter) {
        return this.intersect(inter);
    }

    public Conjunto subtrair(Conjunto dif) {
        return this.subtract(dif);
    }
}

