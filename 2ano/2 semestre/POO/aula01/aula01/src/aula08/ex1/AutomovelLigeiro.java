package aula08.ex1;

public class AutomovelLigeiro extends Veiculo{
    private String numQuadro;
    private int capMala;

    public AutomovelLigeiro(String matricula, String marca, String modelo, int potencia, String numQuadro, int capMala){
        super(matricula,marca,modelo,potencia);
        this.numQuadro=numQuadro;
        this.capMala=capMala;

    }

    @Override
    public String info(){
        return String.format("Marca: %s, Modelo: %s, Matricula: %s, Potencia: %.2f, Número do quadro: %s, Capacidade da mala: %d",
                marca, modelo, matricula, potencia, numQuadro,capMala);
    }
    @Override
    public String toString() {
        return "Automóvel Ligeiro{" +"Marca='" + marca + '\'' +", Modelo='" + modelo + '\'' +", Matricula='" + matricula + '\'' +", Potência=" + potencia + " CV" +", Número do quadro='" + numQuadro + '\'' +", Capacidade da mala=" + capMala + " L" +'}';
    }

}
