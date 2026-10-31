package aula03;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Notas {
    
    // Função para calcular a nota final
    public static int calcularNotaFinal(double notaP, double notaT) {
        // Se a nota prática ou teórica for inferior a 7, o aluno é reprovado
        if (notaP < 7.0 || notaT < 7.0) {
            return 66;
        } else {
            // Caso contrário, calcula a nota final com o peso das componentes
            return (int) Math.round(0.4 * notaT + 0.6 * notaP);
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Lista de alunos
        List<String[]> alunos = new ArrayList<>();
        
        // Caminho do ficheiro (assumindo que está na mesma pasta do projeto)
        String caminhoFicheiro = "alunos.txt";  // Nome do ficheiro
        
        try {
            // Abrir o ficheiro
            File ficheiro = new File(caminhoFicheiro);
            Scanner fileScanner = new Scanner(ficheiro);
            
            // Leitura das linhas do ficheiro
            while (fileScanner.hasNextLine()) {
                String linha = fileScanner.nextLine();
                String[] partes = linha.split("\t"); // Divide a linha pelo separador de tabulação
                
                // Verifica se a linha tem 3 partes: nome, notaT, e notaP
                if (partes.length == 3) {
                    String nome = partes[0];
                    double notaT = Double.parseDouble(partes[1]);
                    double notaP = Double.parseDouble(partes[2]);
                    
                    // Armazenar o nome e as notas
                    alunos.add(new String[] {nome, String.format("%.1f", notaT), String.format("%.1f", notaP)});
                } else {
                    System.out.println("Linha mal formatada: " + linha);
                }
            }
            
            fileScanner.close();
            
            // Cabeçalho da tabela
            System.out.println("\nTabela de Resultados:");
            System.out.printf("%-20s %-10s %-10s %-10s\n", "Nome", "NotaT", "NotaP", "Pauta");
            
            // Processamento das notas e exibição dos resultados
            for (String[] aluno : alunos) {
                String nome = aluno[0];
                double notaT = Double.parseDouble(aluno[1]);
                double notaP = Double.parseDouble(aluno[2]);
                int notaFinal = calcularNotaFinal(notaP, notaT);
                
                System.out.printf("%-20s %-10.1f %-10.1f %-10d\n", nome, notaT, notaP, notaFinal);
            }
            
        } catch (FileNotFoundException e) {
            System.out.println("Ficheiro não encontrado: " + caminhoFicheiro);
        }
        
        scanner.close();
    }
}
