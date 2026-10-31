package aula11ex2;

public class StandardCostCalculator {
    public static double calculate(int emails, double minutos) {
        double custoEmail = 0.0;
        double custoMinuto = 0.10;
        return emails * custoEmail + minutos * custoMinuto;
    }
}
