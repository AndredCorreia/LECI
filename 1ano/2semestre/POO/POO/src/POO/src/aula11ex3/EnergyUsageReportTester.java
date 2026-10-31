package aula11ex3;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class EnergyUsageReportTester {

    public static void main(String[] args) throws IOException {

        EnergyUsageReport energyReport = new EnergyUsageReport();

        energyReport.load("datafiles/aula11/ex3/clients.txt");

        Customer newCustomer = new Customer(999, new LinkedList<>(List.of(1500.0, 2000.0, 2500.0, 3000.0)));
        energyReport.addCustomer(newCustomer);

        energyReport.removeCustomer(1015);

        Customer retrievedCustomer = energyReport.getCustomer(1025);

        double totalEnergyUsage = energyReport.calculateTotalUsage(1003);
        System.out.println("Total energy usage for customer 1003: " + totalEnergyUsage);

        energyReport.generateReport("datafiles/aula11/ex3/energy_report.txt");
    }
}
