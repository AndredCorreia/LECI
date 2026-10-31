package aula04;
import java.util.List;
import java.util.ArrayList;

class Product {
    private String name;
    private double price;
    private int quantity;

    public Product(String name, double price, int quantity) {
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    public double getTotalValue() {
        return price * quantity;
    }

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    public int  getQuantity() {
        return quantity;
    }
    public double getTotal(){
        return quantity*price;
 
    }
    @Override
    public String toString() {
        return String.format("%-10s\t%-6.2f\t%-8d\t%-8.2f", name, price, quantity, getTotal());
    }
}



class CashRegister {
    private List <Product> products= new ArrayList<>();
    public void addProduct(Product product){
        products.add(product);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Product     \tPrice   Quantity    \tTotal\n");
        double totalValue = 0;
        for (Product product : products) {
            sb.append(product.toString()).append("\n");
            totalValue += product.getTotal();
        }
        sb.append("\n");
        sb.append(String.format("Total value: %.2f", totalValue));
        return sb.toString();
    }

}

public class CashRegisterDemo {

    public static void main(String[] args) {

        // Cria e adiciona 5 produtos
        CashRegister cr = new CashRegister();
        cr.addProduct(new Product("Book", 9.99, 3));
        cr.addProduct(new Product("Pen", 1.99, 10));
        cr.addProduct(new Product("Headphones", 29.99, 2));
        cr.addProduct(new Product("Notebook", 19.99, 5));
        cr.addProduct(new Product("Phone case", 5.99, 1));
        
        // TODO: Listar o conteúdo e valor total
        System.out.println(cr);

    }
}