package aula08ex3;

import java.util.*;

public class CarrinhoDeCompras implements Compra {
    private Map<Produto, Integer> produtos;

    public CarrinhoDeCompras() {
        produtos = new LinkedHashMap<>();
    }

    @Override
    public void adicionarProduto(Produto produto, int quantidade) {
        if (quantidade <= 0) {
            System.out.println("Quantidade inválida: " + quantidade);
            return;
        }

        if (produto.getQuantidade() < quantidade) {
            System.out.println("Stock insuficiente para " + produto.getNome());
            return;
        }

        produto.removerQuantidade(quantidade);

        produtos.put(produto, produtos.getOrDefault(produto, 0) + quantidade);
    }

    @Override
    public void listarProdutos() {
        if (produtos.isEmpty()) {
            System.out.println("Carrinho vazio.");
            return;
        }

        System.out.println("Produtos no carrinho:");
        for (Map.Entry<Produto, Integer> entrada : produtos.entrySet()) {
            Produto p = entrada.getKey();
            int quantidade = entrada.getValue();
            System.out.printf("- %s | Preço: %.2f€ | Quantidade: %d\n", p.getNome(), p.getPreco(), quantidade);
        }
    }

    @Override
    public double calcularTotal() {
        double total = 0;
        for (Map.Entry<Produto, Integer> entrada : produtos.entrySet()) {
            total += entrada.getKey().getPreco() * entrada.getValue();
        }
        return total;
    }
}
