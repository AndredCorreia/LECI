package aula02;
import java.util.Scanner;


public class Frase {
    public static void main(String[] args) {
        Scanner scanner= new Scanner(System.in);
        System.out.println("Insira uma frase: ");
        String frase= scanner.nextLine();
        String lowerfrase= frase.toLowerCase();  
        char []lastdigit= frase.toCharArray();
        String primeiros_tres= frase.substring(0,3);

        
        
        System.out.println(lowerfrase);   
        System.out.println(lastdigit[lastdigit.length-1]); 
        System.out.println(primeiros_tres);;  
        scanner.close();
    }

}
