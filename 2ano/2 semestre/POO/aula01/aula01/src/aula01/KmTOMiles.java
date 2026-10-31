package aula01;
import java.util.Scanner;

public class KmTOMiles {
    public static void main(String[] args) {
        double km, miles;
        Scanner sc= new Scanner (System.in);
        System.out.println("Insira distância em km: ");
        km= sc.nextDouble();
        miles= km/1.609;
        System.out.println("A distância em milhas é " + miles);
        sc.close();
    }
}
