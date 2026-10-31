package aula08ex2;

public class PratoDieta extends Prato {
    private double limiteCalorias;

    public PratoDieta(String nome, double limiteCalorias) {
        super(nome);
        this.limiteCalorias = limiteCalorias;
    }

    @Override
    public boolean addIngrediente(Alimento alimento) {
        if (getTotalCalorias() + alimento.getCalorias() > limiteCalorias) {
            System.out.println("Erro: Adicionar " + alimento + " ultrapassa o limite de calorias.");
            return false;
        }
        return super.addIngrediente(alimento);
    }

    @Override
    public String toString() {
        return "Prato Dieta (máx " + limiteCalorias + " cal) - " + super.toString();
    }
}

