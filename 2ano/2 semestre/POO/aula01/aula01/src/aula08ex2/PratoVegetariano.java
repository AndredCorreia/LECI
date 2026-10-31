package aula08ex2;

public class PratoVegetariano extends Prato {

    public PratoVegetariano(String nome) {
        super(nome);
    }

    @Override
    public boolean addIngrediente(Alimento alimento) {
        if (!alimento.eVegetariano()) {
            System.out.println("Erro: " + alimento + " não é vegetariano.");
            return false;
        }
        return super.addIngrediente(alimento);
    }

    @Override
    public String toString() {
        return "Prato Vegetariano - " + super.toString();
    }
}
