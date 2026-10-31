package aula02;
import java.util.Scanner;

public class Dist_2pontos {
    public static void main(String[] args) {
        Scanner scanner= new Scanner(System.in);

        System.out.println("Insira a coordenada x do ponto: ");
        float xp1= scanner.nextFloat();
        System.out.println("Insira a coordenada y do ponto: ");
        float yp1= scanner.nextFloat();

        System.out.println("Insira a coordenada x do outro ponto: ");
        float xp2= scanner.nextFloat();
        System.out.println("Insira a coordenada y do outro ponto: ");
        float yp2= scanner.nextFloat();

        float dist= (yp2-yp1)/(xp2-xp1);
        System.out.println(dist);



        scanner.close();
    }

}
