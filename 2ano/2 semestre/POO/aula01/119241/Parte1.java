import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;





public class Parte1 {
    // -----------------------------------------------------
    //          !!! Não alterar este código !!!
    // -----------------------------------------------------
    private static int v1;
    private static List<Integer> v2 = new ArrayList<>();
    private static String v3;
    private static List<String> v4 = new ArrayList<>();
    // -----------------------------------------------------

    // -----------------------------------------------------------
    // >> Pode acrescentar novos métodos aqui (não é obrigatório)
    // -----------------------------------------------------------

    // pex., public static void ler(SOURCE) {}

    // -----------------------------------------------------------

    public static void lerTeclado() {
        Scanner scanner= new Scanner(System.in);

        System.out.println("Insira um número: ");
        v1 = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Insira uma lista de números: ");
        String linhaV2 = scanner.nextLine().trim();
        if (!linhaV2.isEmpty()) {
            String[] partes = linhaV2.split("\\s*,\\s*");
            for (String parte : partes) {
                v2.add(Integer.parseInt(parte));
            }
        }
        System.out.println("Insira uma frase: ");
        v3 = scanner.nextLine();

        System.out.println("Insira uma lista de frases: ");

        String linhaV4 = scanner.nextLine().trim();
        if (!linhaV4.isEmpty()) {
            String[] partes = linhaV4.split("\\s*,\\s*");
            for (String parte : partes) {
                v4.add(parte.replaceAll("^\"|\"$", ""));
                }
            }
        
        System.out.println(v1);
        System.out.println(v2);

        System.out.println(v3);
        System.out.println(v4);

    }

    

    public static void lerFicheiro() {
        String caminhoFicheiro = "inputs.txt";  // Abrir o ficheiro
        
        try{
            File ficheiro = new File(caminhoFicheiro);
            Scanner fileScanner = new Scanner(ficheiro);


            int linhas = Integer.parseInt(fileScanner.nextLine().trim());

            v1 = Integer.parseInt(fileScanner.nextLine().trim());

            String[] numeros = fileScanner.nextLine().trim().split("\\s+");
            v2.clear();
            for (String num : numeros) {
                v2.add(Integer.parseInt(num));
            }

            v3 = fileScanner.nextLine();

            String[] palavras = fileScanner.nextLine().trim().split("\\s+");
            v4.clear();
            for (String palavra : palavras) {
                v4.add(palavra);
            }

            fileScanner.close();

        }catch (FileNotFoundException e) {
            System.out.println("Ficheiro não encontrado: " + caminhoFicheiro);
        }
    
}

    public static void imprimir() {
        System.out.println("v1: " + v1);
        System.out.println("v2: " + v2);
        System.out.println("v3: " + v3);
        System.out.println("v4: " + v4);


    }

    public static void main(String[] args) {
        // -----------------------------------------------------------------
        // !!! Não imprimir texto a pedir determinado input, ler direto !!!
        // -----------------------------------------------------------------

        // pode editar livremente este código
        //lerTeclado();
        lerFicheiro();
        imprimir();
    }
}