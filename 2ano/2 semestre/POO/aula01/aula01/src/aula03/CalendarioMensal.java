package aula03;
import java.util.Scanner;

public class CalendarioMensal {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int[] dados = lerDataEDiaInicial(scanner);
        int mes = dados[0];
        int ano = dados[1];
        int diaInicio = dados[2];

        int diasDoMes = diasNoMes(mes, ano);

        imprimirCalendario(mes, ano, diaInicio, diasDoMes);

        scanner.close();
    }

    public static int[] lerDataEDiaInicial(Scanner scanner) {
        int mes, ano, diaInicio;
        
        while (true) {
            try {
                System.out.print("Digite a data no formato mm/yyyy: ");
                String entrada = scanner.next();
                String[] partes = entrada.split("/");
                
                if (partes.length != 2) {
                    throw new NumberFormatException();
                }

                mes = Integer.parseInt(partes[0]);
                ano = Integer.parseInt(partes[1]);

                if (mes < 1 || mes > 12 || ano < 1) {
                    throw new IllegalArgumentException("Mês deve estar entre 1 e 12, e o ano deve ser positivo.");
                }

                System.out.print("Digite o dia da semana do primeiro dia do mês (1 = Segunda, ..., 7 = Domingo): ");
                diaInicio = scanner.nextInt();

                if (diaInicio < 1 || diaInicio > 7) {
                    throw new IllegalArgumentException("O dia da semana deve estar entre 1 e 7.");
                }

                return new int[]{mes, ano, diaInicio};

            } catch (Exception e) {
                System.out.println("Entrada inválida! Tente novamente.");
                scanner.nextLine();
            }
        }
    }

    public static int diasNoMes(int mes, int ano) {
        int[] diasPorMes = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) {
            return 29;
        }
        
        return diasPorMes[mes - 1];
    }

    public static void imprimirCalendario(int mes, int ano, int diaInicio, int diasDoMes) {
        String[] diasSemana = {"Seg", "Ter", "Qua", "Qui", "Sex", "Sáb", "Dom"};

        System.out.println("\nCalendário de " + mes + "/" + ano);
        for (String dia : diasSemana) {
            System.out.print(dia + "\t");
        }
        System.out.println();

        int posicao = diaInicio - 1;
        for (int i = 0; i < posicao; i++) {
            System.out.print("\t");
        }

        for (int dia = 1; dia <= diasDoMes; dia++) {
            System.out.printf("%d\t", dia);
            posicao++;
            if (posicao == 7) {
                System.out.println();
                posicao = 0;
            }
        }

        System.out.println("\n");
    }
}
