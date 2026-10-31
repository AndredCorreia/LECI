package aula07;

public class ObraDigital extends Obra {
    private String blockchain;
    private String enderecoContrato;

    public ObraDigital(String nome, String autor, double precoBase, String blockchain, String enderecoContrato) {
        super(nome, autor, precoBase);
        this.blockchain = blockchain;
        this.enderecoContrato = enderecoContrato;
    }

    @Override
    public String detalhes() {
        return String.format("Obra Digital (NFT): %s, Autor: %s, Preço: %.2f, Blockchain: %s, Endereço do Contrato: %s",
                             nome, autor, precoBase, blockchain, enderecoContrato);
    }
}
