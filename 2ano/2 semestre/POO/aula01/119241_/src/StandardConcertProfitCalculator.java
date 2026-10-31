public class StandardConcertProfitCalculator  implements IConcertProfitCalculator{
    public double calculateConcertProfit(boolean nacional, boolean peninsula, double duracao, int id){
        double custo;
        custo=1500/60*duracao;
        if (!nacional) {
            custo = custo*2;
        } 
        if (!peninsula){
            custo+=800;
        }
        return custo;
    }
}


