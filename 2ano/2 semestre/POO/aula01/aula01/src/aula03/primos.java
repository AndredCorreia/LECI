package aula03;
    import java.util.Scanner;

public class primos {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Integer numero;
        Integer soma=17;
        
        while(true){
            System.out.println("Insira um número: ");
            
            if (scanner.hasNextInt()){
                numero= scanner.nextInt();
                if(numero>0){
                    break;
                }
                else{
                    System.out.println("O número tem de ser positivo!");
                }
            

             }
            else{
                System.out.println("Caracter inválido! Insira um número.");
            }
        
        }
        
        switch (numero) {
            case 1:
                System.out.println("É um número primo, e a soma é 1");
                break;
            case 2:
                System.out.println("É um número primo, e a soma é 3");
                break;
            case 3:
                System.out.println("É um número primo, e a soma é 6");
                break;
            case 4:
                System.out.println("Não é um número primo, e a soma é 6");
                break;
            case 5:
                System.out.println("É um número primo, e a soma é 11");
                break;
            case 6:
                System.out.println("Não é um número primo, e a soma é 11");
            case 7:
                System.out.println("É um número primo, e a soma é 18");
            default:
                Integer primo=0;
                for (Integer i=8;i<numero+1;i++){
                    
                    if (i%2==0 || i%3==0 ||i%5==0 || i%7==0){
                        primo=0;
                    }
                    else{
                        primo=1;
                        soma+=i;
                    }

                }
                if (primo==0){
                    System.out.println("O número "+numero+" não é primo, e a soma é "+soma+"!");
                }
                else{
                    System.out.println("O número "+numero+" é primo, e a soma é "+soma+"!");
                }
                break;
        }
        
        
        
        scanner.close();
        
        
    }
}
