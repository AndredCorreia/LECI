package aula03;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public class LeitorDePalavras {
    public static void main(String[] args) throws IOException {
        Scanner input = new Scanner(new FileReader("words.txt"));

        List<String> palavras = new ArrayList<>();

        while (input.hasNext()) {
            String word = input.next();
            System.out.println(word);

            if (word.length() > 2) {
                palavras.add(word);
            }
        }
        input.close();

        System.out.println("\nPalavras terminadas em 's':");
        for (String palavra : palavras) {
            if (palavra.endsWith("s")) {
                System.out.println(palavra);
            }
        }

        Iterator<String> iterator = palavras.iterator();
        while (iterator.hasNext()) {
            String palavra = iterator.next();
            if (!palavra.matches("[a-zA-Z]+")) {
                iterator.remove();
            }
        }

        System.out.println("\nPalavras finais (somente letras): " + palavras);
    }
}
