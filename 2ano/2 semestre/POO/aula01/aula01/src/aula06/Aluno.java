package aula06;
import aula05.DateYMD;

class Aluno extends Pessoa {
    private static int contadorNMec = 100;
    private int nMec;
    private DateYMD dataInsc;

    public Aluno(String nome, int cc, DateYMD dataNasc, DateYMD dataInsc) {
        super(nome, cc, dataNasc);
        this.nMec = contadorNMec++;
        this.dataInsc = dataInsc;
    }

    public Aluno(String nome, int cc, DateYMD dataNasc) {
        this(nome, cc, dataNasc, new DateYMD(1, 1, 2025)); 
    }

    public int getNMec() {
        return nMec;
    }

    @Override
    public String toString() {
        return super.toString() + "; NMec: " + nMec + "; Data de Inscrição: " + dataInsc;
    }
}