package aula08ex2;

public class Carne extends Alimento{
    public enum Variedade{VACA,PORCO,PERU,FRANGO,OUTRA};
    private Variedade variedade;

    public Carne( Variedade variedade,double proteinas, double calorias, double peso){
        super(proteinas,calorias,peso);
        this.variedade=variedade;
    }
    
    @Override
    public boolean eVegetariano() {
        return false;
    }
    @Override
    public String toString() {
        return "Carne (" + variedade + ") - " + super.toString();
    }

}
