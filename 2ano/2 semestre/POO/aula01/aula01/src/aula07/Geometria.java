package aula07;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

abstract class Forma {
    protected String cor;

    public Forma(String cor) {
        this.cor = cor;
    }

    public abstract double area();
    public abstract double perimetro();

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Forma forma = (Forma) obj;
        return this.cor.equals(forma.cor);
    }
}

public class Geometria {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<Forma> figuras = new ArrayList<>();

        while (true) {
            System.out.println("\nEscolha a figura:");
            System.out.println("1. Círculo");
            System.out.println("2. Triângulo");
            System.out.println("3. Retângulo");
            System.out.println("4. Listar figuras");
            System.out.println("5. Comparar figuras");
            System.out.println("0. Sair");

            int escolha = scanner.nextInt();
            scanner.nextLine(); 

            switch (escolha) {
                case 1:
                    System.out.println("Digite o raio: ");
                    double raio = scanner.nextDouble();
                    scanner.nextLine();
                    System.out.println("Digite a cor: ");
                    String corCirculo = scanner.nextLine();
                    figuras.add(new Circulo(raio, corCirculo));
                    break;
                
                case 2:
                    System.out.println("Insira o primeiro lado: ");
                    int lado1 = scanner.nextInt();
                    System.out.println("Insira o segundo lado: ");
                    int lado2 = scanner.nextInt();
                    System.out.println("Insira o terceiro lado: ");
                    int lado3 = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println("Digite a cor: ");
                    String corTriangulo = scanner.nextLine();
                    figuras.add(new Triangulo(lado1, lado2, lado3, corTriangulo));
                    break;
                
                case 3:
                    System.out.println("Insira o comprimento: ");
                    int comprimento = scanner.nextInt();
                    System.out.println("Insira a altura: ");
                    int altura = scanner.nextInt();
                    scanner.nextLine();
                    System.out.println("Digite a cor: ");
                    String corRetangulo = scanner.nextLine();
                    figuras.add(new Retangulo(altura, comprimento, corRetangulo));
                    break;
                
                case 4:
                    System.out.println("\nFiguras cadastradas:");
                    for (Forma figura : figuras) {
                        System.out.println(figura);
                    }
                    break;
                
                case 5:
                    compararFiguras(figuras);
                    break;
                
                case 0:
                    System.out.println("Saindo...");
                    scanner.close();
                    return;
                
                default:
                    System.out.println("Opção inválida!");
            }
        }
    }

    public static void compararFiguras(List<Forma> figuras) {
        for (int i = 0; i < figuras.size(); i++) {
            for (int j = i + 1; j < figuras.size(); j++) {
                Forma figura1 = figuras.get(i);
                Forma figura2 = figuras.get(j);
                if (figura1.equals(figura2)) {
                    System.out.println(figura1 + " é igual a " + figura2);
                } else {
                    System.out.println(figura1 + " é diferente de " + figura2);
                }
            }
        }
    }
}

