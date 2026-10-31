package aula06;
import aula05.DateYMD;

class Bolseiro extends Aluno {
    private Professor orientador;
    private double bolsa;

    public Bolseiro(String nome, int cc, DateYMD dataNasc, Professor orientador, double bolsa) {
        super(nome, cc, dataNasc);
        this.orientador = orientador;
        this.bolsa = bolsa;
    }

    public void setBolsa(double bolsa) {
        this.bolsa = bolsa;
    }

    public double getBolsa() {
        return bolsa;
    }

    public Professor getOrientador() {
        return orientador;
    }

    @Override
    public String toString() {
        return super.toString() + "; Bolsa: " + bolsa + "; Orientador: " + orientador.getNome();
    }
}