package aula08.ex1;

public class PesadoMercadorias extends Veiculo {
    private int numQuadro;
    private int peso;
    private int cargaMaxima;

    public PesadoMercadorias(String matricula, String marca, String modelo, int potencia, int numQuadro, int peso, int cargaMaxima){
        super(matricula, marca, modelo, potencia);
        this.numQuadro=numQuadro;
        this.peso=peso;
        this.cargaMaxima=cargaMaxima;
    }

    @Override
    public String info(){
        return String.format("Marca: %s, Modelo: %s, Matricula: %s, Potencia: %.2f, Número do quadro: %.2f, Peso: %.2f, Carga Máxima: %.2f",
            marca, modelo, matricula, potencia, numQuadro,peso, cargaMaxima);
    }

}
