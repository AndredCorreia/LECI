package aula07;
import java.util.Scanner;

public class MainGaleria {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Galeria galeria = new Galeria();
        int opcao = 0;
        
        do {
            System.out.println("\nMenu:");
            System.out.println("1. Adicionar uma obra");
            System.out.println("2. Listar obras");
            System.out.println("3. Vender uma obra");
            System.out.println("4. Calcular o lucro total");
            System.out.println("5. Sair");
            System.out.print("Opção: ");
            opcao = sc.nextInt();
            sc.nextLine(); 

            switch (opcao) {
                case 1:
                    System.out.println("\n1. Adicionar uma obra do tipo:");
                    System.out.println("1. Quadro");
                    System.out.println("2. Escultura");
                    System.out.println("3. Obra Digital (NFT)");
                    System.out.print("Tipo de produto: ");
                    int opcaoProduto = sc.nextInt();
                    sc.nextLine(); 

                    switch (opcaoProduto) {
                        case 1:
                            System.out.print("Nome do Quadro: ");
                            String nomeQuadro = sc.nextLine();
                            System.out.print("Autor do Quadro: ");
                            String autorQuadro = sc.nextLine();
                            System.out.print("Preço Base: ");
                            double precoQuadro = sc.nextDouble();
                            sc.nextLine();
                            System.out.print("Tipo de Tinta (óleo, guache, aguarela): ");
                            String tipoTinta = sc.nextLine();
                            System.out.print("Está emoldurado? (sim/não): ");
                            boolean emoldurado = sc.nextLine().equalsIgnoreCase("sim");
                            System.out.print("Tamanho da Tela (S, M, L, XL): ");
                            String tamanhoTela = sc.nextLine();
                            galeria.adicionarObra(new Quadro(nomeQuadro, autorQuadro, precoQuadro, tipoTinta, emoldurado, tamanhoTela));
                            break;

                        case 2:
                            System.out.print("Nome da Escultura: ");
                            String nomeEscultura = sc.nextLine();
                            System.out.print("Autor da Escultura: ");
                            String autorEscultura = sc.nextLine();
                            System.out.print("Preço Base: ");
                            double precoEscultura = sc.nextDouble();
                            sc.nextLine();
                            System.out.print("Material (madeira, cerâmica, metal): ");
                            String material = sc.nextLine();
                            System.out.print("Exemplares: ");
                            int exemplares = sc.nextInt();
                            galeria.adicionarObra(new Escultura(nomeEscultura, autorEscultura, precoEscultura, material, exemplares));
                            break;

                        case 3:
                            System.out.print("Nome da Obra Digital (NFT): ");
                            String nomeNFT = sc.nextLine();
                            System.out.print("Autor da Obra Digital: ");
                            String autorNFT = sc.nextLine();
                            System.out.print("Preço Base: ");
                            double precoNFT = sc.nextDouble();
                            sc.nextLine();  
                            System.out.print("Blockchain (Ethereum, Polygon, Solana): ");
                            String blockchain = sc.nextLine();
                            System.out.print("Endereço do Contrato (em hexadecimal): ");
                            String enderecoContrato = sc.nextLine();
                            galeria.adicionarObra(new ObraDigital(nomeNFT, autorNFT, precoNFT, blockchain, enderecoContrato));
                            break;
                    }
                    break;

                case 2:
                    galeria.listarObras();
                    break;

                case 3:
                    System.out.print("Informe o ID da obra a vender: ");
                    int idVenda = sc.nextInt();
                    System.out.print("Informe o preço de venda: ");
                    double precoVenda = sc.nextDouble();
                    galeria.venderObra(idVenda, precoVenda);
                    break;

                case 4:
                    System.out.println("Lucro total: " + galeria.calcularLucroTotal());
                    break;

                case 5:
                    System.out.println("Saindo...");
                    break;

                default:
                    System.out.println("Opção inválida!");
            }
        } while (opcao != 5);

        sc.close();
    }
}
