public class Travel {
    private static int nextId = 1;

    private int id;
    private String partida;
    private String destino;
    private int duracao;

    public Travel(String partida, String destino, int duracao) {
        this.id = nextId++;
        this.partida = partida;
        this.destino = destino;
        this.duracao = duracao;
    }

    public int getId() {
        return id;
    }

    public String getPartida() {
        return partida;
    }

    public String getDestino() {
        return destino;
    }

    public int getDuracao() {
        return duracao;
    }

    public boolean isNacional() {
        String paisOrigem = partida.substring(partida.indexOf(",") + 2).trim();
        String paisDestino = destino.substring(destino.indexOf(",") + 2).trim();
        return paisOrigem.equals(paisDestino);
    }

    @Override
    public String toString() {
        return "Travel ID: " + id + " | " + partida + " -> " + destino + " | " + duracao + " dias";
    }
}
