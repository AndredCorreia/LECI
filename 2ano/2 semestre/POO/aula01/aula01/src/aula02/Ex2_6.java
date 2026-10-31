package aula02;
import java.util.Scanner;
public class Ex2_6 {
    public static void main(String[] args) {
        Scanner scanner= new Scanner (System.in);
        System.out.println("Insira uma frase: ");
        String frase= scanner.nextLine();

        System.out.println("Nº digitos: " +countDigits(frase));
        System.out.println("Nº espaços: " +countSPaces(frase));
        System.out.println("É só minúsculas? " +minusculas(frase));
        System.out.println("Frase com um só espaço: " + espacos(frase));
        System.out.println("Palindromo? " + isPalindrome(frase));
        
        scanner.close();
    }

    public static int countDigits(String s){
        Integer numero=0;
        char []letras= s.toCharArray();
        for (Integer i=0;i<s.length();i++){
            if (Character.isDigit(letras[i])){
                numero++;
            }
        }
        return numero;
    }

    public static int countSPaces(String s){
        Integer espacos=0;
        char []letras=s.toCharArray();
        for (Integer i=0;i<s.length();i++){
            if (letras[i]==' '){
                espacos++;
            }
        }
        return espacos;
    }
    public static boolean minusculas(String s){
        String mini= s.toLowerCase();
        if (mini==s){
            return true;
        }
        else{
            return false;
        }
    }
    public static String espacos(String s){                 //PERGUNTAR AO PROFESSOR!
        String so_um_espaco = s.replaceAll("\\s+", " ");
        return(so_um_espaco);
        
    }  
    public static Boolean isPalindrome(String s){
        char[]letras=s.toCharArray();
        Integer verdade=0;
        for (Integer i=0;i<s.length()-1;i++){
            if (letras[i]!=letras[s.length()-i-1]){
                verdade++;
                
            }
        }
        return verdade==0;
            
                
            
        
    }
}

