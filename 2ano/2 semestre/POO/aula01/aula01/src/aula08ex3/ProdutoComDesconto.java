package aula08ex3;

public class ProdutoComDesconto extends ProdutoGenerico {

    private double desconto; 

    public ProdutoComDesconto(String nome, int stock, double preco, double desconto) {
        super(nome, stock, preco);
        this.desconto = desconto;
    }

    public double getDesconto() {
        return desconto;
    }

    public double getPrecoComDesconto() {
        return preco * (1 - desconto / 100);
    }

    @Override
    public String toString() {
        return String.format("Produto: %s | Preço Original: %.2f€ | Desconto: %.1f%% | Preço com Desconto: %.2f€ | Stock: %d unidades",
                nome, preco, desconto, getPrecoComDesconto(), stock);
    }
}
