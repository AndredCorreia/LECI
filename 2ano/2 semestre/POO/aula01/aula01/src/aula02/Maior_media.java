package aula02;
import java.util.Scanner;


public class Maior_media {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Insira um número: ");
        double numero= scanner.nextDouble();

        double maior= numero;
        double total= numero;
        double menor= numero;
        int times= 1;
        double number=0;
        while (number!=numero){
            System.out.println("Insira outro número: ");
            number= scanner.nextDouble();
            times++;
            total=total+number;
            if (menor>number){
                menor=number;
            }
            if (maior<number){
                maior=number;
            }
        }
        double media= total/times;
        System.out.println("O maior número é: "+maior);
        System.out.println("O menor número é: "+menor);
        System.out.println("A média é: "+media);
        System.out.println("Introduziu "+times+" números");



        scanner.close();
    }

}
