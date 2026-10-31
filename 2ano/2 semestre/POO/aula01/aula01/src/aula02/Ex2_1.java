package aula02;
import java.util.Scanner;

public class Ex2_1 {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);

            System.out.println("Insira um número: ");
            int segundos = scanner.nextInt();

            int horas= segundos/3600;
            int minutos= (segundos%3600)/60;
            segundos= (segundos%3600)%60;
            String S1=String.format("%02d:%02d:%02d\n", horas,minutos,segundos);
            System.out.println(S1);

            scanner.close();
        }
}
