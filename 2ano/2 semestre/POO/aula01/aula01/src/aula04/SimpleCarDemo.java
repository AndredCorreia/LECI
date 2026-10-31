package aula04;
import java.util.Scanner;

class Car {
    public String make;
    public String model;
    public int year;
    public int kms;

    public Car(String make, String model, int year, int kms) {
        this.make = make;
        this.model = model;
        this.year = year;
        this.kms = kms;
    }

    public void drive(int distance) {
        this.kms+=distance;
    }

@Override
    public String toString() {
        return String.format("%s %s (%d) - %d km", make, model, year, kms);
    }
}
public class SimpleCarDemo {

    static Scanner sc = new Scanner(System.in);

    static void listCars(Car[]cars) {
        
        System.out.println("Carros registados:\n");
        for (Car car: cars){   
            System.out.println(car);

        } 
        System.out.println("\n");
       
    }
    
    public static void main(String[] args) {

        Car[]cars = new Car[3];
        cars[0] = new Car ("Renault", "Megane Sport Tourer",2015,35356);
        cars[1] = new Car("Toyota","Camry", 2015, 32456);
        cars[2] = new Car ("Merceder","Vito", 2008, 273891);

        listCars(cars);

        for (int i=0; i<10; i++) {
            int j = (int)Math.round(Math.random()*2); 
            int kms = (int)Math.round(Math.random()*1000); 
            System.out.printf("Carro %d viajou %d quilómetros.\n", j, kms);
            cars[j].drive(kms);

            
            // TODO: adicionar viagem ao carro j

        }

        listCars(cars);

        sc.close();

    }
}
