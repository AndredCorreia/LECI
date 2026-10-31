package aula04;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;


class Circulo{
    double raio;
    Circulo (double r) {
        raio=r;
    }

    double Area(){
        return Math.PI*raio*raio;
    }
    double Perimetro(){
        return Math.PI*2*raio;
    }

    @Override
    public String toString() {
        return "Círculo: raio = " + raio;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Circulo circulo = (Circulo) obj;
        return Double.compare(circulo.raio, raio) == 0;
    }
}
class Triangulo{
    Integer lado1, lado2, lado3;
    Triangulo(Integer l1, Integer l2, Integer l3){
        lado1=l1;
        lado2=l2;
        lado3=l3;
    }
    double Area(){
        double p=(lado1+lado2+lado3)/2;
        return Math.sqrt(p*(p-lado1)*(p-lado2)*(p-lado3));

    }
    Integer Perimetro(){
        return lado1+lado2+lado3;
    }
    @Override
    public String toString() {
        return "Triângulo: lado1 = " + lado1 + ", lado2 = " + lado2 + ", lado3 = " + lado3;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Triangulo triangulo = (Triangulo) obj;
        return Double.compare(triangulo.lado1, lado1) == 0 &&
               Double.compare(triangulo.lado2, lado2) == 0 &&
               Double.compare(triangulo.lado3, lado3) == 0;
    }
}
class Retangulo{
    Integer altura, comprimento;
    Retangulo (Integer a,Integer c){
        altura=a;
        comprimento=c;
    }
    Integer Area(){
        return comprimento*altura;
    }
    Integer Perimetro(){
        return comprimento*2+altura*2;
    }
    @Override
    public String toString() {
        return "Retângulo: altura = " + altura + ", comprimento = " + comprimento;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Retangulo retangulo = (Retangulo) obj;
        return Double.compare(retangulo.altura, altura) == 0 &&
               Double.compare(retangulo.comprimento, comprimento) == 0;
    }
}
public class geometria {
    public static void main(String[] args) {
        Scanner scanner= new Scanner(System.in);
        List <Object> figuras= new ArrayList<>();

        while (true) {
            System.out.println("\nEscolha a figura:");
            System.out.println("1. Círculo");
            System.out.println("2. Triângulo");
            System.out.println("3. Retângulo");
            System.out.println("4. Listar figuras");
            System.out.println("5. Comparar figuras");
            System.out.println("0. Sair");

            int escolha = scanner.nextInt();

            switch (escolha){
                case 1:
                    System.out.println("Digite o raio: ");
                    double raio= scanner.nextDouble();
                    figuras.add(new Circulo(raio));
                    break;
        
                case 2:
                    System.out.println("Insira o primeiro lado: ");
                    int lado1= scanner.nextInt();
                    System.out.println("Insira o segundo lado: ");
                    int lado2= scanner.nextInt();
                    System.out.println("Insira o terceiro lado: ");
                    int lado3= scanner.nextInt();
                    figuras.add(new Triangulo(lado1,lado2,lado3));
                    break;
                case 3:
                    System.out.println("Insira o comprimento: ");
                    int comprimento= scanner.nextInt();
                    System.out.println("Insira a altura: ");
                    int altura= scanner.nextInt();
                    figuras.add(new Retangulo(comprimento, altura));
                    break;
                case 4:
                    System.out.println("\nFiguras:");
                    for (Object figura : figuras){
                        System.out.println(figura);
                    }
                    break;
                case 5:
                    compararFiguras(figuras);
                    break;
                case 0:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
                default:
                    System.out.println("Insira uma opção válida!");
            }
        }

    }

    public static void compararFiguras(List<Object> figuras) {
        for (int i = 0; i < figuras.size(); i++) {
            for (int j = i + 1; j < figuras.size(); j++) {
                Object figura1 = figuras.get(i);
                Object figura2 = figuras.get(j);

                if (figura1.getClass() == figura2.getClass()) {
                    if (figura1.equals(figura2)) {
                        System.out.println(figura1 + " é igual a " + figura2);
                    } else {
                        System.out.println(figura1 + " é diferente de " + figura2);
                    }
                }
            }
        }
    }
}
