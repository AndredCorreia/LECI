package aula07;


import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        DateYMD data = null;

        while (true) {
            System.out.println("Date operations: ");
            System.out.println("1 - create new date");
            System.out.println("2 - show current date");
            System.out.println("3 - increment date");
            System.out.println("4 - decrement date");
            System.out.println("0 - exit");

            int opcao = scanner.nextInt();
            switch (opcao) {
                case 1 -> {
                    System.out.print("Dia: ");
                    int day = scanner.nextInt();
                    System.out.print("Mês: ");
                    int month = scanner.nextInt();
                    System.out.print("Ano: ");
                    int year = scanner.nextInt();

                    try {
                        data = new DateYMD(day, month, year);
                        System.out.println("Data criada com sucesso: " + data);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Erro: " + e.getMessage());
                    }
                }
                case 2 -> {
                    if (data == null) {
                        System.out.println("Nenhuma data foi criada ainda!");
                    } else {
                        System.out.println("Data atual: " + data);
                    }
                }
                case 3 -> {
                    if (data == null) {
                        System.out.println("Cria uma data primeiro!");
                    } else {
                        System.out.print("Quantos dias queres adicionar? ");
                        int dias = scanner.nextInt();
                        data.incrementar(dias);
                        System.out.println("Nova data: " + data);
                    }
                }
                case 4 -> {
                    if (data == null) {
                        System.out.println("Cria uma data primeiro!");
                    } else {
                        System.out.print("Quantos dias queres remover? ");
                        int dias = scanner.nextInt();
                        data.decrementar(dias);
                        System.out.println("Nova data: " + data);
                    }
                }
                case 0 -> {
                    System.out.println("Saindo...");
                    scanner.close();
                    return;
                }
                default -> System.out.println("Opção inválida! Tente novamente.");
            }
        }
    }
}
