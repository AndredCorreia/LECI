package aula02;
import java.util.Scanner;
import java.lang.Math;

public class hipotenusa {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Insira o valor do primeiro cateto: ");
        double c1= scanner.nextFloat();
        System.out.println("Insira o valor do segundo cateto: ");
        double c2= scanner.nextFloat();

        double hipotenusa= Math.sqrt(c1*c1+c2*c2);
        System.out.println(hipotenusa);



        scanner.close();
    }

}
