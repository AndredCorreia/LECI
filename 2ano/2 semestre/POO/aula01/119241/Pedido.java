public class Pedido extends Pacote{
    private static int contadorNumSequencia=10;
    private int numSequencia;
    private String mensagem;

    public Pedido(String source, String destino, int numSequencia, String mensagem){
        super(source,destino);
        this.numSequencia=contadorNumSequencia++;
        this.mensagem=mensagem;
    }

    public int getNumSequencia(){
        return numSequencia;
    }
    public String getMensagem(){
        return mensagem;
    }
    public String toString() {
        return "Pedido {" +"source='" + getSource() + '\'' + ", destino='" + getDestino() + '\'' +", numeroSequencia=" + getNumSequencia() +", mensagem='" + getMensagem() + '\'' +'}';
    }
}