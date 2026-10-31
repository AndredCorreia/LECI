package aula08ex3;

public class ProdutoGenerico implements Produto{
    protected String nome;
    protected int stock;
    protected double preco;

    public ProdutoGenerico(String nome, int stock,double preco){
        this.nome=nome;
        this.stock=stock;
        this.preco=preco;
    }

    public String getNome() {
        return nome;
    }
    public int getStock() {
        return stock;
    }
    public double getPreco() {
        return preco;
    }
    @Override
    public int getQuantidade() {
        return 100;
    }
    @Override
    public void adicionarQuantidade(int quantidade) {
        if (quantidade > 0) {
            stock += quantidade;
        }
    }

    @Override
    public void removerQuantidade(int quantidade) {
        if (quantidade > 0 && quantidade <= stock) {
            stock -= quantidade;
        } else if (quantidade > stock) {
            System.out.println("Quantidade a remover excede o stock disponível.");
        }
    }

    @Override
    public String toString() {
        return String.format("Produto: %s | Preço: %.2f€ | Stock: %d unidades", nome, preco, stock);
    }
}
