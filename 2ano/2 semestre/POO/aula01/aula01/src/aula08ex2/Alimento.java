package aula08ex2;

public abstract class Alimento {
    protected double proteinas;
    protected double calorias;
    protected double peso;


    public Alimento (double proteinas, double calorias, double peso){
        this.proteinas=proteinas;
        this.calorias=calorias;
        this.peso=peso;
    }

    public double getProteinas(){
        return proteinas;
    }
    public double getCalorias(){
        return calorias;
    }
    public double getPeso(){
        return peso;
    }
    public abstract boolean eVegetariano();

    @Override
    public String toString() {
        return String.format("Proteínas: %.2f, Calorias: %.2f, Peso: %.2f", proteinas, calorias, peso);
    }
}


