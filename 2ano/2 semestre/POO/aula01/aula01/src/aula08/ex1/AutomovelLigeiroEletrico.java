package aula08.ex1;

public class AutomovelLigeiroEletrico extends AutomovelLigeiro implements IGestaoBateria{
    private double cargaBateria;
    private double cargaMaxima;

    public AutomovelLigeiroEletrico(String marca, String modelo, String matricula, int potencia, String numQuadro, int capMala){
        super(marca,modelo,matricula,potencia,numQuadro,capMala);
        this.cargaBateria=100.0;
        this.cargaMaxima=100.0;

    }

    @Override
    public double cargaDisponivel() {
        return cargaBateria;
    }

    @Override
    public void carregar(double percentagem) {
        cargaBateria += percentagem;
        if (cargaBateria > cargaMaxima) {
            cargaBateria = cargaMaxima;
        }
    }

    @Override
    public void limitarCargaMaxima(double percentagem) {
        this.cargaMaxima = percentagem;
        if (cargaBateria > cargaMaxima) {
            cargaBateria = cargaMaxima;
        }
    }

    @Override
    public String info() {
        return super.info() + String.format(", Bateria: %.2f%%", cargaBateria);
    }
}
    


