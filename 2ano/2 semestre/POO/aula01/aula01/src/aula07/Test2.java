package aula07;
public class Test2 {
    public static void main(String[] args) {
        DateND dateND = new DateND(10000);  
        System.out.println(dateND);  

        dateND.incrementar(5);  
        System.out.println(dateND);

        dateND.decrementar(2);   
        System.out.println(dateND);

        DateYMD dateYMD = dateND.toDateYMD();
        System.out.println("Data convertida para DateYMD: " + dateYMD);
    }
}
