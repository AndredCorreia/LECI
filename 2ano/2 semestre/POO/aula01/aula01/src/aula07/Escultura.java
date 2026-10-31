package aula07;

public class Escultura extends Obra {
    private String material;
    private int exemplares;

    public Escultura(String nome, String autor, double precoBase, String material, int exemplares) {
        super(nome, autor, precoBase);
        this.material = material;
        this.exemplares = exemplares;
    }

    @Override
    public String detalhes() {
        return String.format("Escultura: %s, Autor: %s, Preço: %.2f, Material: %s, Exemplares: %d",
                             nome, autor, precoBase, material, exemplares);
    }
}
