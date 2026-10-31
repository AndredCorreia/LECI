package aula09ex2;

import java.util.Scanner;

public class PlaneTester {
    public static void main(String[] args) {
        PlaneManager manager = new PlaneManager();
        Scanner scanner = new Scanner(System.in);
        int opcao;

        do {
            System.out.println("\n--- Menu de Gestão da Frota de Aviões ---");
            System.out.println("1. Adicionar avião comercial");
            System.out.println("2. Adicionar avião militar");
            System.out.println("3. Remover avião");
            System.out.println("4. Procurar avião");
            System.out.println("5. Imprimir todos os aviões");
            System.out.println("6. Listar aviões comerciais");
            System.out.println("7. Listar aviões militares");
            System.out.println("8. Mostrar avião mais rápido");
            System.out.println("0. Sair");
            System.out.print("Escolhe uma opção: ");
            opcao = scanner.nextInt();

            switch (opcao) {
                case 1 -> {
                    System.out.print("ID: ");
                    int id = scanner.nextInt();
                    scanner.nextLine(); 
                    System.out.print("Modelo: ");
                    String modelo = scanner.nextLine();
                    System.out.print("Ano de produção: ");
                    int ano = scanner.nextInt();
                    System.out.print("Nº máximo de passageiros: ");
                    int maxPass = scanner.nextInt();
                    System.out.print("Velocidade máxima: ");
                    int velMax = scanner.nextInt();
                    System.out.print("Nº de passageiros: ");
                    int passageiros = scanner.nextInt();

                    CommercialPlane cp = new CommercialPlane(id, modelo, ano, maxPass, velMax, passageiros);
                    manager.addPlane(cp);
                    System.out.println("Avião comercial adicionado!");
                }
                case 2 -> {
                    System.out.print("ID: ");
                    int id = scanner.nextInt();
                    scanner.nextLine(); 
                    System.out.print("Modelo: ");
                    String modelo = scanner.nextLine();
                    System.out.print("Ano de produção: ");
                    int ano = scanner.nextInt();
                    System.out.print("Nº máximo de passageiros: ");
                    int maxPass = scanner.nextInt();
                    System.out.print("Velocidade máxima: ");
                    int velMax = scanner.nextInt();
                    System.out.print("Nº de munições: ");
                    int municoes = scanner.nextInt();

                    MilitaryPlane mp = new MilitaryPlane(id, modelo, ano, maxPass, velMax, municoes);
                    manager.addPlane(mp);
                    System.out.println("Avião militar adicionado!");
                }
                case 3 -> {
                    System.out.print("ID do avião a remover: ");
                    int id = scanner.nextInt();
                    boolean removido = manager.removePlane(id);
                    if (removido) {
                        System.out.println("Avião removido com sucesso.");
                    } else {
                        System.out.println("Avião não encontrado.");
                    }
                }
                case 4 -> {
                    System.out.print("ID do avião a procurar: ");
                    int id = scanner.nextInt();
                    Plane p = manager.searchPlane(id);
                    if (p != null) {
                        System.out.println("Avião encontrado:");
                        System.out.println(p);
                    } else {
                        System.out.println("Avião não encontrado.");
                    }
                }
                case 5 -> {
                    System.out.println("\n--- Frota Completa ---");
                    manager.printAllPlanes();
                }
                case 6 -> {
                    System.out.println("\n--- Aviões Comerciais ---");
                    for (CommercialPlane cp : manager.getCommercialPlanes()) {
                        System.out.println(cp);
                    }
                }
                case 7 -> {
                    System.out.println("\n--- Aviões Militares ---");
                    for (MilitaryPlane mp : manager.getMilitaryPlanes()) {
                        System.out.println(mp);
                    }
                }
                case 8 -> {
                    Plane fastest = manager.getFastestPlane();
                    if (fastest != null) {
                        System.out.println("Avião mais rápido:");
                        System.out.println(fastest);
                    } else {
                        System.out.println("A frota está vazia.");
                    }
                }
                case 0 -> System.out.println("A sair...");
                default -> System.out.println("Opção inválida.");
            }
        } while (opcao != 0);

        scanner.close();
    }
}
