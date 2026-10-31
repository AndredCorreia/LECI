package aula11ex2;


public class Contact {
    private static int nextId=1;
    private final int id;
    private String nome;
    private int numeroTel;
    private String email;
    private String dataNascimento;
     

    public Contact(String nome, int numeroTel, String email, String dataNascimento){
        this.id= nextId++;
        this.nome=nome;
        this.numeroTel=numeroTel;
        this.email=email;
        this.dataNascimento=dataNascimento;
    }

    public int getId(){
        return id;
    }
    public String getNome(){
        return nome;
    }
    public int getNumeroTel(){
        return numeroTel;
    }
    public String getEmail(){
        return email;
    }
    public String getDataNascimento(){
        return dataNascimento;
    }
    public void setNome(String nome){
        this.nome=nome;
    }
    public void setNumeroTel(int numeroTel){
        this.numeroTel=numeroTel;
    }
    public void setEmail(String email){
        this.email=email;
    }
    public void setDataNascimento(String dataNascimento){
        this.dataNascimento=dataNascimento;
    }
    
    
    @Override
    public String toString() {
        return String.format("Nome: %s, Telemóvel: %d, Email: %s, Data de Nascimento: %s", nome, numeroTel, email, dataNascimento);
    }
}
