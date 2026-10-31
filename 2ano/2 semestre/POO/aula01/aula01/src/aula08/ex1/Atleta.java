package aula08.ex1;

public class Atleta implements KmPercorridos{
    private String nome;
    private int distanciaTotal;
    private int ultimoTreino;
    private Veiculo viaturaAlugada;
    private Telemovel telemovel;


    public Atleta(String nome){
        this.nome=nome;
        this.distanciaTotal=0;
        this.ultimoTreino=0;
    }
    public Telemovel getTelemovel(){
        return telemovel;
    }
    public Veiculo getViaturaAlugada() {
        return viaturaAlugada;
    }

    public void setViaturaAlugada(Veiculo viaturaAlugada) {
        this.viaturaAlugada = viaturaAlugada;
    }

    public void trajeto(int quilometros){
        this.distanciaTotal+=quilometros;
        this.ultimoTreino=quilometros;
    }
    public int ultimoTrajeto(){
        return (ultimoTreino);

    }
    public int distanciaTotal(){
        return(distanciaTotal);

    }
    public String getNome(){
        return nome;
    }

    public void alugarViatura(Veiculo viatura){
        this.viaturaAlugada=viatura;
        System.out.println("Atleta "+nome+" alugou a viatura: "+viatura);
    }

    @Override
    public String toString() {
        return "Atleta{" +"nome='" + nome + '\'' +", distanciaTotal=" + distanciaTotal +", ultimoTreino=" + ultimoTreino +'}';
}


}
