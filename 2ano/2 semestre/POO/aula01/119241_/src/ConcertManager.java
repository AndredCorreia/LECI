import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class ConcertManager {
    private Map<Integer, Concert> concerts = new HashMap<>();
    private IConcertProfitCalculator calculateConcertProfit = new StandardConcertProfitCalculator();

    
    public void addConcert(Concert c){
        concerts.put(c.getId(), c);
    }

    public void removeConcert(int id){
        concerts.remove(id);
    }

    public Concert getConcert(int id){
        return concerts.get(id);
    }

    public void printAllConcerts() {
        for (Concert c : concerts.values()) {
            System.out.println(c);
        }
    }

    public double calculateConcertProfit(int id) {
        Concert c = concerts.get(id);
        if (c == null) {
            System.out.println("Concerto com ID " + id + " não encontrada.");
            return -1;
        }
        return calculateConcertProfit.calculateConcertProfit(c.isNacional(),c.isPeninsula(), c.getDuracao(), c.getId());
    }

    public void readFile(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split(";");
                
                double duracao = Double.parseDouble(partes[1].trim());
                String local = partes[2].trim();
                String horario = partes[3].trim();
    
                Concert c = new Concert(local,horario,duracao);
                addConcert(c);
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o ficheiro: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Erro ao converter número: " + e.getMessage());
        }
    }

    public void writeFile(String filename) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            for (Concert c : concerts.values()) {
                writer.printf("%d; %s; %s; %s -> Lucro:%s euros.%n",
                        c.getId(), c.getDuracao(), c.getLocal(), c.getHorario(),calculateConcertProfit(c.getId()));
            }
        } catch (IOException e) {
            System.out.println("Erro ao escrever no ficheiro: " + e.getMessage());
        }
    }


}
