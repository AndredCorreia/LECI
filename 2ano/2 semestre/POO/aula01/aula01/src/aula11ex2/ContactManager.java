package aula11ex2;

import java.io.*;
import java.util.*;

public class ContactManager {
    private Map<Integer, Contact> contactos = new HashMap<>();
    private int totalEmailsEnviados = 0;
    private double totalMinutosChamada = 0.0;

    public void addContact(Contact c) {
        if (contactos.containsKey(c.getId())) {
            System.out.println("Contato já existe.");
        } else {
            contactos.put(c.getId(), c);
        }
    }

    public void removeContact(int id) {
        contactos.remove(id);
    }

    public Contact getContact(int id) {
        return contactos.get(id);
    }

    public void sendEmail(int id) {
        if (contactos.containsKey(id)) {
            totalEmailsEnviados++;
            System.out.println("Email enviado para " + contactos.get(id).getEmail());
        } else {
            System.out.println("Contato não encontrado.");
        }
    }

    public void call(int id, double minutes) {
        if (contactos.containsKey(id)) {
            totalMinutosChamada += minutes;
            System.out.println("Chamada de " + minutes + " minutos feita para " + contactos.get(id).getNome());
        } else {
            System.out.println("Contato não encontrado.");
        }
    }

    public double calculateContactCost() {
        return StandardCostCalculator.calculate(totalEmailsEnviados, totalMinutosChamada);
    }

    public void printAllContacts() {
        for (Contact c : contactos.values()) {
            System.out.println(c);
        }
    }

    public void readFile(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String linha;
            while ((linha = reader.readLine()) != null) {
                String[] partes = linha.split("/t");
                String nome = partes[0];
                int numeroTel = Integer.parseInt(partes[1]);
                String email = partes[2];
                String dataNascimento = partes[3];
                Contact c = new Contact(nome, numeroTel, email, dataNascimento);
                addContact(c);
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o ficheiro: " + e.getMessage());
        }
    }

    public void writeFile(String filename) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            for (Contact c : contactos.values()) {
                writer.printf("%s;%d;%s;%s%n",
                        c.getNome(), c.getNumeroTel(), c.getEmail(), c.getDataNascimento());
            }
        } catch (IOException e) {
            System.out.println("Erro ao escrever no ficheiro: " + e.getMessage());
        }
    }
}
