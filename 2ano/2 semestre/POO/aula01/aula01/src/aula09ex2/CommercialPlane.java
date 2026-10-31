package aula09ex2;

public class CommercialPlane extends Plane{
    private int numPassageiros;


    public CommercialPlane(int id, String modelo, int anoProducao, int numMaxPassageiros, int VelocidadeMax, int numPassageiros){
        super(id,modelo,anoProducao,numMaxPassageiros,VelocidadeMax);
        this.numPassageiros=numPassageiros;
        }

    public int getNumPassageiros(){
        return numPassageiros;
    }

    @Override
    public String getPlaneType(){
        return ("Comercial");
    }
    @Override
    public String toString(){
        return String.format("ID: %d, Modelo: %s, Ano de Produção: %d, Número máximo de passageiros: %d, Número de passageiros: %d, Velocidade Máxima: %d", 
        getId(),getModelo(),getAnoProducao(),getNumMaxPassageiros(),getNumPassageiros(),getVelocidadeMax());
    }
}

//%d->inteiro, %s->String, %f ->decimal(.2f,.3f(casas decimais)),float/double, %b->boleano, %c ->char