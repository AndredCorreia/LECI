package aula02;
import java.util.Scanner;

public class Acronimo {
    public static void main(String[] args) {
        Scanner scanner= new Scanner(System.in);
        System.out.println("Insira uma frase: ");
        String frase= scanner.nextLine();
        String acronim= new String();
        
        String[] palavras = frase.split(" ");
        
        for (String palavra : palavras) {
            char []inicial=palavra.toCharArray();
            if (palavra.length()>=3){
                acronim+=(inicial[0]);

            }

        }
        System.out.println(acronim);
        scanner.close(); 
    }
      
}
