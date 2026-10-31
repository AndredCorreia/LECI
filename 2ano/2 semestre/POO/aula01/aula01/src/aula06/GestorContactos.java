package aula06;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class GestorContactos {
    private List<Contacto> contactos;
    
    public GestorContactos() {
        this.contactos = new ArrayList<>();
    }

    public void inserirContacto(Pessoa pessoa, String telemovel, String email) {
        for (Contacto c : contactos) {
            if (c.getPessoa().getNome().equals(pessoa.getNome())) {
                System.out.println("A pessoa já tem um contacto registado. Deseja continuar? (S/N)");
                Scanner scanner = new Scanner(System.in);
                String resposta = scanner.nextLine();
                if (resposta.equalsIgnoreCase("N")) {
                    scanner.close();
                    return;
                }
                scanner.close();
            }
        }
        contactos.add(new Contacto(pessoa, telemovel, email));
        System.out.println("Contacto inserido com sucesso!");
    }

    public void alterarContacto(int id, String novoTelemovel, String novoEmail) {
        for (Contacto c : contactos) {
            if (c.getId() == id) {
                c.setTelemovel(novoTelemovel);
                c.setEmail(novoEmail);
                System.out.println("Contacto alterado com sucesso!");
                return;
            }
        }
        System.out.println("Contacto não encontrado!");
    }

    public void apagarContacto(int id) {
        contactos.removeIf(c -> c.getId() == id);
        System.out.println("Contacto apagado com sucesso!");
    }

    public Contacto procurarContacto(String nome) {
        for (Contacto c : contactos) {
            if (c.getPessoa().getNome().equals(nome)) {
                return c;
            }
        }
        return null;
    }

    public void listarContactos() {
        if (contactos.isEmpty()) {
            System.out.println("Não há contactos para listar.");
            return;
        }
        for (Contacto c : contactos) {
            System.out.println(c);
        }
    }
}
