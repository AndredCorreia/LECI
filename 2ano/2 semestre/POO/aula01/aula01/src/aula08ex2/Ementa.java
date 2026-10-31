package aula08ex2;

import java.util.*;

public class Ementa {
    private String nome;
    private String local;
    private List<PratoDia> pratos;

    public Ementa(String nome, String local) {
        this.nome = nome;
        this.local = local;
        this.pratos = new ArrayList<>();
    }

    public enum DiaSemana {
        SEGUNDA, TERCA, QUARTA, QUINTA, SEXTA, SABADO, DOMINGO
    }

    private static class PratoDia {
        Prato prato;
        DiaSemana dia;

        PratoDia(Prato prato, DiaSemana dia) {
            this.prato = prato;
            this.dia = dia;
        }
    }

    public void addPrato(Prato p, DiaSemana dia) {
        pratos.add(new PratoDia(p, dia));
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (PratoDia pd : pratos) {
            sb.append(pd.dia).append(": ").append(pd.prato).append("\n");
        }
        return nome + " - " + local + "\n" + sb.toString();
    }
}
