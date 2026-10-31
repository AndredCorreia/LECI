package aula08.ex1;

public class Main {
    public static void main(String[] args) {
        EmpresaAluguer empresa = new EmpresaAluguer("RentCar", "3810-193", "rentcar@mail.com");

        AutomovelLigeiro a1 = new AutomovelLigeiro("AA-11-11", "Toyota", "Yaris", 90, "123456", 300);
        Taxi t1 = new Taxi("AB-12-34", "Mercedes", "Classe A", 120, "654321", 400, 300);

        Motociclo m1 = new Motociclo("AC-33-33", "Honda", "CBR500", 50, "desportivo");

        empresa.addViatura(a1);
        empresa.addViatura(t1);
        empresa.addViatura(m1);

        Atleta atleta = new Atleta("João Silva");

        empresa.alugarViaturaAoAtleta(atleta);
        

        atleta.trajeto(15); 
        atleta.trajeto(20); 

        a1.trajeto(100);
        t1.trajeto(200);
        m1.trajeto(50);

        System.out.println(atleta);

        System.out.println("Todas as viaturas:");
        empresa.listarViaturas();
        
        Veiculo viaturaMenosKms = empresa.viaturaComMenosKms();
        Veiculo viaturaMaisKms = empresa.viaturaComMaisKms();

        System.out.println("\nViatura com menos quilómetros: " + viaturaMenosKms);
        System.out.println("Viatura com mais quilómetros: " + viaturaMaisKms);

        Telemovel telemovel1 = new Telemovel();
        Telemovel telemovel2 = new Telemovel();

        Atleta atleta1 = new Atleta("John Doe");
        Atleta atleta2 = new Atleta("Jane Smith");
        
        
        System.out.println("Atleta 1: " + atleta1.getNome());
        //System.out.println("Telemóvel: " + atleta1.getTelemovel());
        //System.out.println("Status da Bateria: " + atleta1.getTelemovel().cargaDisponivel() + "%");
        
        System.out.println("Atleta 2: " + atleta2.getNome());
        //System.out.println("Telemóvel: " + atleta2.getTelemovel());
        //System.out.println("Status da Bateria: " + atleta2.getTelemovel().cargaDisponivel() + "%");

        if (telemovel1.cargaDisponivel() < 40) {
            telemovel1.carregar(40); 
        }

        telemovel1.limitarCargaMaxima(80);
        System.out.println("Após carregar, Telemóvel 1 Bateria: " + telemovel1.cargaDisponivel() + "%");
        telemovel2.limitarCargaMaxima(30);
        System.out.println("Após carregar, Telemóvel 2 Bateria: " + telemovel2.cargaDisponivel() + "%");
        
        AutomovelLigeiroEletrico carroEletrico = new AutomovelLigeiroEletrico("Tesla", "Model 3", "ABC123", 250, "QWERTY123", 500);
        
        System.out.println("\nAutomóvel Elétrico: " + carroEletrico.info());
        System.out.println("Status da Bateria: " + carroEletrico.cargaDisponivel() + "%");
        
        carroEletrico.limitarCargaMaxima(80);
        System.out.println("Após limitar, Automóvel Elétrico Bateria: " + carroEletrico.cargaDisponivel() + "%");
    }
        
    }

