import java.io.*;
import java.util.*;

public class TravelManager {
    private Map<Integer, Travel> travels = new HashMap<>();
    private ITravelCostCalculator calculator = new StandardTravelCostCalculator();

    public void addTravel(Travel t){
        travels.put(t.getId(), t);
    }

    public void removeTravel(int id){
        travels.remove(id);
    }

    public Travel getTravel(int id){
        return travels.get(id);
    }

    public void printAllTravels() {
        for (Travel t : travels.values()) {
            System.out.println(t);
        }
    }

    public String sortTravelsByCost(boolean nacional) {
        List<Travel> lista = new ArrayList<>();
        for (Travel t : travels.values()) {
            if (t.isNacional() == nacional) {
                lista.add(t);
            }
        }

        lista.sort(Comparator.comparingDouble(t ->
                calculator.calculate(t.isNacional(), t.getDuracao(), t.getId())
        ));

        for (Travel t : lista) {
            System.out.printf("%s | Custo: %.2f€%n", t, calculator.calculate(t.isNacional(), t.getDuracao(), t.getId()));
        }
        return "";
    }

    public double calculateTravelCost(int id) {
        Travel t = travels.get(id);
        if (t == null) {
            System.out.println("Viagem com ID " + id + " não encontrada.");
            return -1;
        }
        return calculator.calculate(t.isNacional(), t.getDuracao(), t.getId());
    }

    public void readFile(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split(";");
                
                int duracao = Integer.parseInt(partes[1].trim());
                String partida = partes[2].trim();
                String destino = partes[3].trim();
    
                Travel t = new Travel(partida, destino, duracao);
                addTravel(t);
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o ficheiro: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Erro ao converter número: " + e.getMessage());
        }
    }
    

    public void writeFile(String filename) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            for (Travel t : travels.values()) {
                writer.printf("%d;%s;%s;%d;%n",
                        t.getId(), t.getPartida(), t.getDestino(), t.getDuracao());
            }
        } catch (IOException e) {
            System.out.println("Erro ao escrever no ficheiro: " + e.getMessage());
        }
    }
}
