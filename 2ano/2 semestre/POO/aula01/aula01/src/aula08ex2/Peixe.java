package aula08ex2;

public class Peixe extends Alimento{
    public enum Tipo{FRESCO, CONGELADO};
    private Tipo tipo;

    public Peixe(Tipo tipo, double proteinas, double calorias, double peso){
        super(proteinas,calorias,peso);
        this.tipo=tipo;
    }

    @Override
    public boolean eVegetariano() {
        return false;
    }
    @Override
    public String toString() {
        return "Peixe (" + tipo + ") - "+super.toString();
    }

}
