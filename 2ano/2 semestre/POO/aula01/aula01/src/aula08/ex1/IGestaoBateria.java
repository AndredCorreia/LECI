package aula08.ex1;

public interface IGestaoBateria {
    double cargaDisponivel(); 
    void carregar(double percentagem); 
    
    void limitarCargaMaxima(double percentagem); 
    }
