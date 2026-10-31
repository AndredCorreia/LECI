package aula07;

class Triangulo extends Forma {
    private int lado1, lado2, lado3;

    public Triangulo(int lado1, int lado2, int lado3, String cor) {
        super(cor);
        this.lado1 = lado1;
        this.lado2 = lado2;
        this.lado3 = lado3;
    }

    @Override
    public double area() {
        double p = (lado1 + lado2 + lado3) / 2.0;
        return Math.sqrt(p * (p - lado1) * (p - lado2) * (p - lado3));
    }

    @Override
    public double perimetro() {
        return lado1 + lado2 + lado3;
    }

    @Override
    public String toString() {
        return "Triângulo: lados = [" + lado1 + ", " + lado2 + ", " + lado3 + "], cor = " + cor;
    }
}
