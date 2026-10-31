package aula03;
import java.util.Random;
import java.util.Scanner;
public class AltoBaixo {
    public static void main(String[] args) {
        Scanner scanner= new Scanner(System.in);
        String resposta="sim";
        do{
            Random random = new Random();
            int numeroAleatorio = random.nextInt(100) + 1;
            System.out.println("Número aleatório: " + numeroAleatorio);
            Integer guess,tentativas=0;
            
            
            do{
                tentativas++;
                System.out.println("Adivinha o número: ");
                guess= scanner.nextInt();
                if (guess>numeroAleatorio){
                    System.out.println("ALTO!");
                }
                if (guess<numeroAleatorio){
                    System.out.println("BAIXO!");
                }

            }while (guess!=numeroAleatorio);

            System.out.println("Acertou! Precisou de "+tentativas+" tentativas para acertar o número!");
            System.out.println("Deseja jogar novamente? Prima (S)im!");
            resposta=scanner.next().toLowerCase();
        }while(resposta.equals("sim")|| resposta.equals("s")); 
        System.out.println("Obrigado por jogar! Até à próxima!!!");
        scanner.close();
    }
}
