package aula08.ex1;

public class Motociclo extends Veiculo{
    private String tipo;

    public Motociclo(String matricula, String marca, String modelo, int potencia, String tipo){
        super(matricula,marca,modelo,potencia);
        this.tipo=tipo;
    }

    @Override
    public String info(){
        return String.format("Marca: %s, Modelo: %s, Matricula: %s, Potencia: %.2f, tipo: %s",
                marca, modelo, matricula, potencia, tipo);
    }

    @Override
    public String toString(){
        return "Motociclo {"+"Marca: '"+marca+'\''+" Modelo: '"+modelo+'\''+" Matricula: '"+matricula+'\''+" Potencia: '"+potencia+'\''+" Tipo: '"+tipo+'\''+"}";
    }
}
