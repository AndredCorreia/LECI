public class Resposta extends Pacote{

    private int numSequencia;
    private String mensagem;

    public Resposta(String source, String destino, int numSequencia, String mensagem){
        super(source,destino);
        this.numSequencia=getNumSequencia();
        this.mensagem=mensagem;
    }

    

    public String getMensagem(){
        return mensagem;
    }
    public String toString() {
        return "Pedido {" +"source='" + getSource() + '\'' + ", destino='" + getDestino() + '\'' +", numeroSequencia=" + getNumSequencia() +", mensagem='" + getMensagem() + '\'' +'}';
    }
}