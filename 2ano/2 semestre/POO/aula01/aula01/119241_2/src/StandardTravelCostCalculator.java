public class StandardTravelCostCalculator implements ITravelCostCalculator {
    public double calculate(boolean nacional, int duracao, int id){
        double custo;
        
        if (nacional) {
            custo = 50 * duracao;
        } else {
            custo = 150 * duracao;
        }
        if (duracao < 7) {
            custo += 75;
        }
        if (id % 10 == 0) {
            custo *= 0.9;
        }
        return custo;
    }
}
