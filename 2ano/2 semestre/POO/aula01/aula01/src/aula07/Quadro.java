package aula07;

public class Quadro extends Obra {
    private String tipoTinta;
    private boolean emoldurado;
    private String tamanhoTela;

    public Quadro(String nome, String autor, double precoBase, String tipoTinta, boolean emoldurado, String tamanhoTela) {
        super(nome, autor, precoBase);
        this.tipoTinta = tipoTinta;
        this.emoldurado = emoldurado;
        this.tamanhoTela = tamanhoTela;
    }

    @Override
    public String detalhes() {
        return String.format("Quadro: %s, Autor: %s, Preço: %.2f, Tipo de Tinta: %s, Emoldurado: %b, Tamanho da Tela: %s",
                             nome, autor, precoBase, tipoTinta, emoldurado, tamanhoTela);
    }
}

