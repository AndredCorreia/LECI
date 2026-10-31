package aula08ex2;

public class Cereal extends Alimento{
    private String nome;

    public Cereal(String nome, double proteinas, double calorias, double peso){
        super(proteinas, calorias, peso);
        this.nome=nome;
    }
    public String getNome() {
        return nome;
    }
    @Override
    public boolean eVegetariano() {
        return true;
    }
    @Override
    public String toString() {
        return "Cereal ("+nome+") - "+super.toString();
    }

}
