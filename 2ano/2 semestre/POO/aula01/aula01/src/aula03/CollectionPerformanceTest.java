package aula03;

import java.util.*;

public class CollectionPerformanceTest {

    public static void main(String[] args) {
        int[] DIM_VALUES = {1000, 5000, 10000, 20000, 40000, 100000};

        List<Collection<Integer>> collections = Arrays.asList(
                new ArrayList<>(),
                new LinkedList<>(),
                new HashSet<>()
        );

        // Imprime cabeçalho formatado
        System.out.printf("%-15s", "Operação");
        for (int dim : DIM_VALUES) {
            System.out.printf("%12d", dim);
        }
        System.out.println("\n" + "-".repeat(80));

        for (Collection<Integer> col : collections) {
            String colName = col.getClass().getSimpleName();

            System.out.printf("%-15s", colName + " Add");
            for (int dim : DIM_VALUES) {
                System.out.printf("%12.2f", measureAddTime(col, dim));
            }
            System.out.println();

            System.out.printf("%-15s", colName + " Search");
            for (int dim : DIM_VALUES) {
                System.out.printf("%12.2f", measureSearchTime(col, dim));
            }
            System.out.println();

            System.out.printf("%-15s", colName + " Remove");
            for (int dim : DIM_VALUES) {
                System.out.printf("%12.2f", measureRemoveTime(col, dim));
            }
            System.out.println("-".repeat(80)); // Separador entre estruturas
        }
    }

    private static double measureAddTime(Collection<Integer> col, int DIM) {
        col.clear();
        double start = System.nanoTime();
        for (int i = 0; i < DIM; i++) {
            col.add(i);
        }
        return (System.nanoTime() - start) / 1e6;
    }

    private static double measureSearchTime(Collection<Integer> col, int DIM) {
        double start = System.nanoTime();
        for (int i = 0; i < DIM; i++) {
            int n = (int) (Math.random() * DIM);
            col.contains(n);
        }
        return (System.nanoTime() - start) / 1e6;
    }

    private static double measureRemoveTime(Collection<Integer> col, int DIM) {
        double start = System.nanoTime();
        Iterator<Integer> iterator = col.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            iterator.remove();
        }
        return (System.nanoTime() - start) / 1e6;
    }
}
