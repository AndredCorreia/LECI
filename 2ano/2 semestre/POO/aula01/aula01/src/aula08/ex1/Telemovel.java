package aula08.ex1;

public class Telemovel implements IGestaoBateria{
    private double cargaBateria;
    private double cargaMaxima;

    public Telemovel(){
        this.cargaBateria=100.0;
        this.cargaMaxima=100.0;
    }

    @Override  
    public double cargaDisponivel(){
        return cargaBateria;
    }

    @Override
    public void carregar(double percentagem){
        cargaBateria+=percentagem;
        if (cargaBateria>cargaMaxima){
            cargaBateria=cargaMaxima;
        }

    }
    @Override
    public void limitarCargaMaxima(double percentagem){
        this.cargaMaxima=percentagem;
        if (cargaBateria>cargaMaxima){
            cargaBateria=cargaMaxima;
        }
    }
    @Override
    public String toString() {
        return String.format("Telemóvel - Carga: %.2f%%", cargaBateria);
    }
    

}
