package aula07;

class Retangulo extends Forma {
    private int altura, comprimento;

    public Retangulo(int altura, int comprimento, String cor) {
        super(cor);
        this.altura = altura;
        this.comprimento = comprimento;
    }

    @Override
    public double area() {
        return altura * comprimento;
    }

    @Override
    public double perimetro() {
        return 2 * (altura + comprimento);
    }

    @Override
    public String toString() {
        return "Retângulo: altura = " + altura + ", comprimento = " + comprimento + ", cor = " + cor;
    }
}
