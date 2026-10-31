package aula07;

import java.util.ArrayList;
import java.util.List;

public class Galeria {
    private List<Obra> obras;       //lista de objetos do tipo Obra chamada obras
    private double lucroTotal;

    public Galeria() {
        obras = new ArrayList<>();      //cria a lista vazia
        lucroTotal = 0.0;
    }

    public void adicionarObra(Obra obra) {
        obras.add(obra);
    }

    public void listarObras() {
        if (obras.isEmpty()) {
            System.out.println("Nenhuma obra disponível.");
        } else {
            for (Obra obra : obras) {
                System.out.println(obra.detalhes());
            }
        }
    }

    public void venderObra(int id, double precoVenda) {
        for (Obra obra : obras) {
            if (obra.getId() == id) {
                lucroTotal += (precoVenda - obra.getPrecoBase());
                obras.remove(obra);
                System.out.println("Obra " + obra.getNome() + " vendida por " + precoVenda);
                return;  //funciona como um brake, sai do loop e quebra logo o método inteiro
            }
        }
        System.out.println("Obra com ID " + id + " não encontrada.");
    }

    public double calcularLucroTotal() {
        return lucroTotal;
    }
}

