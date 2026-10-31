package aula08.ex1;

public abstract class Veiculo implements KmPercorridos{
    protected String matricula;
    protected String marca;
    protected String modelo;
    protected int potencia;
    private int quilometrosUltimoTrajeto;
    private int quilometrosTotais;



    public Veiculo(String matricula, String marca, String modelo, int potencia){
        this.matricula=matricula;
        this.marca=marca;
        this.modelo=modelo;
        this.potencia=potencia;
    }

    public String getMatricula(){
        return matricula;
    }
    public String getMarca(){
        return marca;
    }
    public String getModelo(){
        return modelo;
    }
    public Integer getPotencia(){
        return potencia;
    }
    public abstract String info();

    @Override
    public void trajeto(int quilometros){
        this.quilometrosUltimoTrajeto= quilometros;
        this.quilometrosTotais+=quilometros;

    }

    @Override
    public int ultimoTrajeto(){
        return quilometrosUltimoTrajeto;
    }
    @Override
    public int distanciaTotal(){
        return quilometrosTotais;
    }

    
    
}


