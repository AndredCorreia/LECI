package aula03;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class StudentGrades {
    public static void main(String[] args) {
        List<String> names = new ArrayList<>();
        List<Double> noteP = new ArrayList<>();
        List<Double> noteT = new ArrayList<>();

        try {
            Scanner input = new Scanner(new FileReader("aula03/data.tsv"));

            while (input.hasNextLine()) {
                String[] parts = input.nextLine().split("\t");

                if (parts.length == 3) {
                    names.add(parts[0]);
                    noteP.add(Double.parseDouble(parts[1]));
                    noteT.add(Double.parseDouble(parts[2]));
                }
            }
            input.close();
        } catch (IOException e) {
            System.out.println("Erro ao ler o ficheiro: " + e.getMessage());
            return;
        }

        if (names.isEmpty()) {
            System.out.println("Nenhum dado válido encontrado.");
            return;
        }

        double avgNoteP = noteP.stream().mapToDouble(Double::doubleValue).average().orElse(0.0);
        double avgNoteT = noteT.stream().mapToDouble(Double::doubleValue).average().orElse(0.0);

        System.out.printf("Média de noteP: %.2f\n", avgNoteP);
        System.out.printf("Média de noteT: %.2f\n", avgNoteT);

        System.out.println("\nAlunos com noteT acima da média:");
        for (int i = 0; i < names.size(); i++) {
            if (noteT.get(i) > avgNoteT) {
                System.out.println(names.get(i));
            }
        }

        System.out.println("\nAlunos com classificação final acima da média:");
        List<Double> finalGrades = new ArrayList<>();
        for (int i = 0; i < names.size(); i++) {
            double finalGrade = 0.4 * noteP.get(i) + 0.6 * noteT.get(i);
            finalGrades.add(finalGrade);
        }
        double avgFinalGrade = finalGrades.stream().mapToDouble(Double::doubleValue).average().orElse(0.0);

        for (int i = 0; i < names.size(); i++) {
            if (finalGrades.get(i) > avgFinalGrade) {
                System.out.printf("%s (%.2f)\n", names.get(i), finalGrades.get(i));
            }
        }
    }
}
