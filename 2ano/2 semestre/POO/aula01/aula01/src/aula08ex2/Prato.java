package aula08ex2;

import java.util.*;

public class Prato {
    private String nome;
    protected List<Alimento> composicao;

    public Prato(String nome) {
        this.nome = nome;
        this.composicao = new ArrayList<>();
    }

    public String getNome() {
        return nome;
    }

    public boolean addIngrediente(Alimento alimento) {
        return composicao.add(alimento);
    }

    public double getTotalCalorias() {
        return composicao.stream().mapToDouble(Alimento::getCalorias).sum();
    }

    public double getTotalProteinas() {
        return composicao.stream().mapToDouble(Alimento::getProteinas).sum();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Prato " + nome + ":\n");
        for (Alimento a : composicao) {
            sb.append("  - ").append(a).append("\n");
        }
        sb.append(String.format("Total calorias: %.2f, Total proteínas: %.2f", 
                                 getTotalCalorias(), getTotalProteinas()));
        return sb.toString();
    }
}
