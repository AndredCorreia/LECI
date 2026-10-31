package aula08.ex1;
import java.util.ArrayList;


public class EmpresaAluguer {
    private String nome;
    private String codigoPostal;
    private String email;
    private ArrayList<Veiculo> viaturas;

    public EmpresaAluguer(String nome, String codigoPostal, String email){
        this.nome=nome;
        this.codigoPostal=codigoPostal;
        this.email=email;
        this.viaturas= new ArrayList<>();
    }


    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCodigoPostal() {
        return codigoPostal;
    }

    public void setCodigoPostal(String codigoPostal) {
        this.codigoPostal = codigoPostal;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }


    public void addViatura(Veiculo v){
        viaturas.add(v);
    }
    
    public void listarViaturas() {
        for (Veiculo v : viaturas) {
            System.out.println(v);
        }
    }
    
    
    public Veiculo viaturaComMenosKms() {
        if (viaturas.isEmpty()) {
            System.out.println("Nenhuma viatura disponível.");
            return null;
        }
    Veiculo viaturaMenosKms = viaturas.get(0); 
    for (Veiculo v : viaturas) {
        if (v.distanciaTotal() < viaturaMenosKms.distanciaTotal()) {
            viaturaMenosKms = v;
        }
    }
    return viaturaMenosKms;

    }
    
    public Veiculo viaturaComMaisKms() {
        if (viaturas.isEmpty()) {
            System.out.println("Nenhuma viatura disponível.");
            return null;
        }

        Veiculo viaturaMaisKms = viaturas.get(0); 
        for (Veiculo v : viaturas) {
            if (v.distanciaTotal() > viaturaMaisKms.distanciaTotal()) {
                viaturaMaisKms = v;
            }
        }
        return viaturaMaisKms;
    }


    public void alugarViaturaAoAtleta(Atleta atleta) {
        Veiculo viaturaMenosKms = viaturaComMenosKms();
        if (viaturaMenosKms != null) {
            atleta.alugarViatura(viaturaMenosKms);
            System.out.println("A viatura com menos quilómetros foi alugada ao atleta " + atleta.getNome());
        } else {
            System.out.println("Não há viaturas disponíveis para alugar.");
        }
    }
    
}
