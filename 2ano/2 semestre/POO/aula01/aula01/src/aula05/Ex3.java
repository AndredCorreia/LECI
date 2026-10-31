package aula05;

import java.util.ArrayList;

class DateYMD {
    private int day, month, year;
    
    public DateYMD(int day, int month, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }
    
    public int getDay() {
        return day;
    }
    
    public int getMonth() {
        return month;
    }
    
    public int getYear() {
        return year;
    }
    
    @Override
    public String toString() {
        return String.format("%04d-%02d-%02d", year, month, day);
    }
}

class Property {
    private static int counter = 1000;
    private int id;
    private String location;
    private int rooms;
    private int price;
    private boolean available;
    private DateYMD auctionStart;
    private DateYMD auctionEnd;
    
    public Property(String location, int rooms, int price) {
        this.id = counter++;
        this.location = location;
        this.rooms = rooms;
        this.price = price;
        this.available = true;
        this.auctionStart = null;
        this.auctionEnd = null;
    }
    
    public int getId() {
        return id;
    }
    
    public boolean isAvailable() {
        return available;
    }
    
    public void sell() {
        if (available) {
            available = false;
            System.out.println("Imóvel " + id + " vendido.");
        } else {
            System.out.println("Imóvel " + id + " não está disponível.");
        }
    }
    
    public void setAuction(DateYMD start, int duration) {
        if (!available) {
            System.out.println("Imóvel " + id + " não está disponível.");
            return;
        }
        this.auctionStart = start;
        this.auctionEnd = new DateYMD(start.getDay() + duration, start.getMonth(), start.getYear());
    }
    
    @Override
    public String toString() {
        String status = available ? "sim" : "não";
        String auctionInfo = (auctionStart != null && auctionEnd != null) ? "; leilão " + auctionStart + " : " + auctionEnd : "";
        return String.format("Imóvel: %d; quartos: %d; localidade: %s; preço: %d; disponível: %s%s", id, rooms, location, price, status, auctionInfo);
    }
}

class RealEstate {
    private ArrayList<Property> properties;
    
    public RealEstate() {
        properties = new ArrayList<>();
    }
    
    public void newProperty(String location, int rooms, int price) {
        properties.add(new Property(location, rooms, price));
    }
    
    public void sell(int id) {
        for (Property p : properties) {
            if (p.getId() == id) {
                p.sell();
                return;
            }
        }
        System.out.println("Imóvel " + id + " não existe.");
    }
    
    public void setAuction(int id, DateYMD start, int duration) {
        for (Property p : properties) {
            if (p.getId() == id) {
                p.setAuction(start, duration);
                return;
            }
        }
        System.out.println("Imóvel " + id + " não existe.");
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Propriedades:\n");
        for (Property p : properties) {
            sb.append(p).append("\n");
        }
        return sb.toString();
    }
}


public class Ex3 {
    public static void main(String[] args) {
        RealEstate imobiliaria = new RealEstate();
        imobiliaria.newProperty("Glória", 2, 30000);
        imobiliaria.newProperty("Vera Cruz", 1, 25000);
        imobiliaria.newProperty("Santa Joana", 3, 32000);
        imobiliaria.newProperty("Aradas", 2, 24000);
        imobiliaria.newProperty("São Bernardo", 2, 20000);

        imobiliaria.sell(1001);
        imobiliaria.setAuction(1002, new DateYMD(21, 3, 2023), 4);
        imobiliaria.setAuction(1003, new DateYMD(1, 4, 2023), 3);
        imobiliaria.setAuction(1001, new DateYMD(1, 4, 2023), 4);
        imobiliaria.setAuction(1010, new DateYMD(1, 4, 2023), 4);

        System.out.println(imobiliaria);

    }
}


