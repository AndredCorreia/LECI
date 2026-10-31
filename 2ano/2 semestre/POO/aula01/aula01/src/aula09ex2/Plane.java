package aula09ex2;

public abstract class Plane {
    protected int id;
    protected String fabricante;
    protected String modelo;
    protected int anoProducao;
    protected int numMaxPassageiros;
    protected int VelocidadeMax;
    
    
    public Plane (int id, String modelo, int anoProducao, int numMaxPassageiros, int VelocidadeMax){
        this.id=id;
        this.modelo=modelo;
        this.anoProducao=anoProducao;
        this.numMaxPassageiros=numMaxPassageiros;
        this.VelocidadeMax=VelocidadeMax;
    }

    public int getId(){
        return id;
    }
    public String getModelo(){
        return modelo;
    }

    public int getAnoProducao(){
        return anoProducao;
    }

    public int getNumMaxPassageiros(){
        return numMaxPassageiros;
    }
    public int getVelocidadeMax(){
        return VelocidadeMax;
    }
    public abstract String getPlaneType();

}
