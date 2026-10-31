package aula07;

public abstract class Obra {
    protected static int contadorId = 33; 
    protected int id;
    protected String nome;
    protected String autor;
    protected double precoBase;

    public Obra(String nome, String autor, double precoBase) {
        this.id = contadorId++;
        this.nome = nome;
        this.autor = autor;
        this.precoBase = precoBase;
    }

    public int getId() {
        return id;
    }

    public String getNome() {
        return nome;
    }

    public String getAutor() {
        return autor;
    }

    public double getPrecoBase() {
        return precoBase;
    }

    public abstract String detalhes();
}
