public class Concert {
    private static int nextId = 1;
    private int id;
    private double duracao;
    private String local;
    private String horario;


    public Concert(String local, String horario, double duracao) {
        this.id = nextId++;
        this.local = local;
        this.horario = horario;
        this.duracao = duracao;
    }

    public int getId() {
        return id;
    }



    public String getLocal() {
        return local;
    }

    public String getHorario() {
        return horario;
    }

    public double getDuracao() {
        return duracao;
    }
    public boolean isNacional() {
        String pais = local.substring(local.indexOf(",") + 2).trim();
        return (pais=="Portugal");
    }
    public boolean isPeninsula() {
        String pais = local.substring(local.indexOf(",") + 2).trim();
        if(pais!= "Espanha") {
            if (pais=="Portugal"){
                return true;
            }
        }
        return false;
    }

    @Override
    public String toString() {
        return ("Concerto : " + id + " | " + local + " | " + horario + " | " + duracao + " minutos");
    }
}


  
