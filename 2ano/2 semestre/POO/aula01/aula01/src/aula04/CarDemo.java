package aula04;
import java.util.Scanner;
class Car {
    public String make;
    public String model;
    public int year;
    public int kms;
 
    public Car(String var1, String var2, int var3, int var4) {
       this.make = var1;
       this.model = var2;
       this.year = var3;
       this.kms = var4;
    }
 
    public void drive(int distancia) {
       this.kms += distancia;
    }
 
    public String toString() {
       return String.format("%s %s (%d) - %d km", this.make, this.model, this.year, this.kms);
    }
 }

public class CarDemo {
    static Scanner sc = new Scanner(System.in);

    static int registerCars(Car[] cars) {
        int count = 0;
        while (count < cars.length) {
            System.out.print("Insira dados do carro (marca modelo ano quilómetros): ");
            String input = sc.nextLine().trim();
            
            if (input.isEmpty()) 
            break; 

            String[] parts = input.split(" ");
            if (parts.length < 4) {
                System.out.println("Dados mal formatados. Tente novamente.");
                continue;
            }

            String make = parts[0]; 
            String model = String.join(" ", java.util.Arrays.copyOfRange(parts, 1, parts.length - 2)); 
            String yearStr = parts[parts.length - 2]; 
            String kmsStr = parts[parts.length - 1]; 

            try {
                int year = Integer.parseInt(yearStr);
                int kms = Integer.parseInt(kmsStr);

                if (year < 1000 || year > 9999 || kms < 0) {
                    throw new NumberFormatException();
                }

                cars[count++] = new Car(make, model, year, kms);
            } catch (NumberFormatException e) {
                System.out.println("Dados mal formatados. Tente novamente.");
            }
        }
        return count;
    }

    static void registerTrips(Car[] cars, int numCars) {
        while (true) {
            System.out.print("Registe uma viagem no formato \"carro:distância\": ");
            String input = sc.nextLine().trim();

            if (input.isEmpty()) 
            break; 

            String[] parts = input.split(":");
            if (parts.length != 2) {
                System.out.println("Dados mal formatados. Tente novamente.");
                continue;
            }

            try {
                int carIndex = Integer.parseInt(parts[0]);
                int distancia = Integer.parseInt(parts[1]);

                if (carIndex < 0 || carIndex >= numCars || distancia < 0) {
                    throw new NumberFormatException();
                }

                cars[carIndex].drive(distancia);
            } catch (NumberFormatException e) {
                System.out.println("Dados mal formatados. Tente novamente.");
            }
        }
    }

    static void listCars(Car[] cars, int numCars) {
        System.out.println("\nCarros registados:");
        for (int i = 0; i < numCars; i++) {
            System.out.println(cars[i]);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Car[] cars = new Car[10];

        int numCars = registerCars(cars);

        if (numCars > 0) {
            listCars(cars, numCars);
            registerTrips(cars, numCars);
            listCars(cars, numCars);
        }

        sc.close();
    }
}
