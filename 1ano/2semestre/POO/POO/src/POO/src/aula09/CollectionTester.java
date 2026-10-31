package aula09;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class CollectionTester {
    public static void main(String[] args) {
        int DIM = 5000;
        Collection<Integer> col = new ArrayList<>();
        checkPerformance(col, DIM);
    }

    private static void checkPerformance(Collection<Integer> col, int DIM) {
        double start, stop, delta;
        
        start = System.nanoTime(); 
        for (int i = 0; i < DIM; i++)
            col.add(i);
        stop = System.nanoTime();  
        delta = (stop - start) / 1e6;  
        System.out.println(col.size() + ": Add to " + col.getClass().getSimpleName() + " took " + delta + "ms");

        // Search
        start = System.nanoTime(); 
        for (int i = 0; i < DIM; i++) {
            int n = (int) (Math.random() * DIM);
            if (!col.contains(n))
                System.out.println("Not found???" + n);
        }
        stop = System.nanoTime();  
        delta = (stop - start) / 1e6;  
        System.out.println(col.size() + ": Search to " + col.getClass().getSimpleName() + " took " + delta + "ms");

        // Remove
        start = System.nanoTime(); 
        Iterator<Integer> iterator = col.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            iterator.remove();
        }
        stop = System.nanoTime();  
        delta = (stop - start) / 1e6;  
        System.out.println(col.size() + ": Remove from " + col.getClass().getSimpleName() + " took " + delta + "ms");
    }
}
