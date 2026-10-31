package aula10ex3;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class EnergyUsageReport {
    private Map<Integer, Customer> customers;

    public EnergyUsageReport() {
        this.customers = new HashMap<>();
    }

    public void load(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;

            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\\|");
                if (parts.length >= 2) {
                    int customerId = Integer.parseInt(parts[0].trim());
                    List<Double> meterReadings = new ArrayList<>();
                    for (int i = 1; i < parts.length; i++) {
                        meterReadings.add(Double.parseDouble(parts[i].trim()));
                    }
                    Customer customer = new Customer(customerId, meterReadings);
                    addCustomer(customer);
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler o ficheiro: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Erro ao converter número: " + e.getMessage());
        }
    }

    public void addCustomer(Customer customer) {
        customers.put(customer.getCustomerId(), customer);
    }

    public void removeCustomer(int customerId) {
        customers.remove(customerId);
    }

    public Customer getCustomer(int customerId) {
        return customers.get(customerId);
    }

    public double calculateTotalUsage(int customerId) {
        Customer customer = customers.get(customerId);
        if (customer != null) {
            double total = 0;
            for (double reading : customer.getMeterReadings()) {
                total += reading;
            }
            return total;
        } else {
            System.err.println("Cliente com ID " + customerId + " não encontrado.");
            return 0;
        }
    }

    public void generateReport(String filename) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            for (Customer customer : customers.values()) {
                double total = calculateTotalUsage(customer.getCustomerId());
                writer.write("ID: " + customer.getCustomerId() + " | Consumo Total: " + total + " kWh");
                writer.newLine();
            }
            System.out.println("Relatório gerado com sucesso: " + filename);
        } catch (IOException e) {
            System.err.println("Erro ao escrever o relatório: " + e.getMessage());
        }
    }
}
