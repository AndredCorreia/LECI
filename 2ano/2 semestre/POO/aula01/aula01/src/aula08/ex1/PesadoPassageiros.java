package aula08.ex1;

public class PesadoPassageiros extends Veiculo {
    private int numQuadro;
    private int peso;
    private int maxPassageiros;

    public PesadoPassageiros(String matricula, String marca, String modelo, int potencia, int numQuadro, int peso, int maxPassageiros){
        super(matricula, marca, modelo, potencia);
        this.numQuadro=numQuadro;
        this.peso=peso;
        this.maxPassageiros=maxPassageiros;
    }

    @Override
    public String info(){
        return String.format("Marca: %s, Modelo: %s, Matricula: %s, Potencia: %.2f, Número do quadro: %.2f, Peso: %.2f, Número máximo de passageiros: %.2f",
            marca, modelo, matricula, potencia, numQuadro,peso,maxPassageiros);
    }
}   
