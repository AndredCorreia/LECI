package aula09ex2;

public class MilitaryPlane extends Plane{
    private int numMunicoes;

    public MilitaryPlane(int id, String modelo, int anoProducao, int numMaxPassageiros, int VelocidadeMax, int numMunicoes){
        super(id,modelo,anoProducao, numMaxPassageiros,VelocidadeMax);
        this.numMunicoes=numMunicoes;
    }

    public int getNumMunicoes(){
        return numMunicoes;
    }

    @Override
    public String getPlaneType(){
        return ("Militar");
    }

    @Override
    public String toString(){
        return String.format("ID: %d, Modelo: %s, Ano de Produção: %d, Número máximo de passageiros: %d, Número de munições: %d, Velocidade Máxima: %d", 
        getId(),getModelo(),getAnoProducao(),getNumMaxPassageiros(),getNumMunicoes(),getVelocidadeMax());
    }

}
