public abstract class Pacote{
    protected String source;
    protected String destino;


    public Pacote(String source, String destino){
        this.source=source;
        this.destino=destino;
    }

    public String getSource(){
        return source;
    }
    public String getDestino(){
        return destino;
    }
    public String toString() {
        return "Pacote{" + "source='" + source + '\'' + ", destino='" + destino + '\'' + '}';
    }
}