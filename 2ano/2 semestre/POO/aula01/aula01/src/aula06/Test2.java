package aula06;
import aula05.DateYMD;
import java.util.Scanner;

public class Test2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        GestorContactos gestor = new GestorContactos();
        
        Pessoa aluno = new Aluno("Andreia Melo", 9855678, new DateYMD(18, 7, 1990), new DateYMD(1, 9, 2018));
        Pessoa professor = new Professor("Jorge Almeida", 3467225, new DateYMD(13, 3, 1967), "Associado", "Informática");
        
        while (true) {
            System.out.println("Gestão de Contactos");
            System.out.println("1 - Inserir contacto");
            System.out.println("2 - Alterar contacto");
            System.out.println("3 - Apagar contacto");
            System.out.println("4 - Procurar contacto");
            System.out.println("5 - Listar contactos");
            System.out.println("0 - Sair");
            int opcao = scanner.nextInt();
            scanner.nextLine();  
            
            switch (opcao) {
                case 1:
                    System.out.println("Inserir contacto");
                    System.out.print("Nome: ");
                    String nome = scanner.nextLine();
                    System.out.print("Telemóvel: ");
                    String telemovel = scanner.nextLine();
                    System.out.print("Email: ");
                    String email = scanner.nextLine();
                    Pessoa pessoa = nome.equals("Andreia Melo") ? aluno : professor;
                    gestor.inserirContacto(pessoa, telemovel, email);
                    break;
                case 2:
                    System.out.println("Alterar contacto");
                    System.out.print("ID do contacto: ");
                    int idAlterar = scanner.nextInt();
                    scanner.nextLine(); 
                    System.out.print("Novo telemóvel: ");
                    String novoTelemovel = scanner.nextLine();
                    System.out.print("Novo email: ");
                    String novoEmail = scanner.nextLine();
                    gestor.alterarContacto(idAlterar, novoTelemovel, novoEmail);
                    break;
                case 3:
                    System.out.println("Apagar contacto");
                    System.out.print("ID do contacto: ");
                    int idApagar = scanner.nextInt();
                    gestor.apagarContacto(idApagar);
                    break;
                case 4:
                    System.out.println("Procurar contacto");
                    System.out.print("Nome: ");
                    String nomeProcurar = scanner.nextLine();
                    Contacto contactoEncontrado = gestor.procurarContacto(nomeProcurar);
                    if (contactoEncontrado != null) {
                        System.out.println(contactoEncontrado);
                    } else {
                        System.out.println("Contacto não encontrado!");
                    }
                    break;
                case 5:
                    System.out.println("Listar contactos");
                    gestor.listarContactos();
                    break;
                case 0:
                    System.out.println("Saindo...");
                    return;
                default:
                    System.out.println("Opção inválida! Tente novamente.");
            }
        scanner.close();
        }
    }
}
