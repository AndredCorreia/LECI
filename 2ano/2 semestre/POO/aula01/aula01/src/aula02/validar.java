package aula02;
import java.util.InputMismatchException;
import java.util.Scanner;

public class validar {
    public static void main(String[] args) {
        Scanner scanner= new Scanner(System.in);
        Integer numero= -3; 
        do{
        System.out.println("Insira um valor entra 0-9: ");
        try{    
            numero= scanner.nextInt();
            if (numero>9 || numero<0){
                System.out.println("Fora do intervalo! Tente novamente!");
            }
        }catch(InputMismatchException e){
            System.out.println("Entrada inválida! Por favor, insira um número inteiro.");
            scanner.nextLine();
        }

        }while (numero>9 || numero<0);
        
        System.out.println("Você inseriu um número válido: " + numero);
        scanner.close();
    }

}
