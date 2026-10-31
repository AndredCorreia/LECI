package aula10ex1;
import java.io.*;
import java.util.*;

public class ContadorParesSimples {

    private static final String SEPARADORES = "[\\t\\n\\.,:'‘’;?!\\-*\\{}=+&/()\\[\\]”“\"']+";

    public static void main(String[] args) {
        String ficheiro = "major.txt"; 

        Map<String, Integer> contagemPares = new LinkedHashMap<>();

        try (BufferedReader leitor = new BufferedReader(new FileReader(ficheiro))) {
            String linha;
            String palavraAnterior = null;

            while ((linha = leitor.readLine()) != null) {
                String[] palavras = linha.split(SEPARADORES);

                for (String palavra : palavras) {
                    palavra = palavra.toLowerCase().trim();
                
                    if (palavra.length() < 3) {
                        palavraAnterior = null;
                        continue;
                    }
                
                    if (palavraAnterior != null) {
                        String par = palavraAnterior + " " + palavra;
                        contagemPares.put(par, contagemPares.getOrDefault(par, 0) + 1);
                    }
                
                    palavraAnterior = palavra;
                }
                
            }

            Map<String, Map<String, Integer>> resultado = new LinkedHashMap<>();

            for (Map.Entry<String, Integer> entrada : contagemPares.entrySet()) {
                String[] palavras = entrada.getKey().split(" ");
                String primeira = palavras[0];
                String segunda = palavras[1];

                resultado.putIfAbsent(primeira, new LinkedHashMap<>());
                resultado.get(primeira).put(segunda, entrada.getValue());
            }

            for (Map.Entry<String, Map<String, Integer>> entrada : resultado.entrySet()) {
                System.out.print(entrada.getKey() + "={");
                List<String> pares = new ArrayList<>();
                for (Map.Entry<String, Integer> seg : entrada.getValue().entrySet()) {
                    pares.add(seg.getKey() + "=" + seg.getValue());
                }
                System.out.println(String.join(", ", pares) + "}");
            }

        } catch (IOException e) {
            System.err.println("Erro ao ler o ficheiro: " + e.getMessage());
        }
    }
}
