package aula08.ex1;

public class Taxi extends Veiculo{
    private String numLicenca;
    private int numQuadro;
    private int capMala;


    public Taxi(String matricula,String marca, String modelo, int potencia, String numLicenca, int numQuadro, int capMala){
        super(matricula, marca, modelo, potencia);
        this.numLicenca=numLicenca;
        this.numQuadro=numQuadro;
        this.capMala=capMala;
    }

    @Override
    public String info(){
        return String.format("Marca: %s, Modelo: %s, Matricula: %s, Potencia: %.2f, Número do quadro: %.2f, Capacidade da mala: %.2f, Número de licença: %s",
            marca, modelo, matricula, potencia, numQuadro,capMala,numLicenca);
    }
    
    @Override
    public String toString(){
        return "Taxi {"+"Marca: '"+marca+'\''+", Modelo: '"+modelo+'\''+", Matricula: '"+matricula+'\''+", Potencia: '"+potencia+'\''+", Número do quadro: '"+numQuadro+'\''+", Capacidade da mala: '"+capMala+'\''+", Número de licença: '"+numLicenca+'\''+"L}";

    }

}
