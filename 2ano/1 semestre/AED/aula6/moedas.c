#include <stdio.h>

int coin_row_problem(int coins[], int n) {
    if (n == 0) return 0;      
    if (n == 1) return coins[0]; 
    
    int V[n+1];
    V[0] = 0;            
    V[1] = coins[0];    

    for (int i = 2; i <= n; i++) {
        V[i] = (coins[i-1] + V[i-2] > V[i-1]) ? coins[i-1] + V[i-2] : V[i-1];
    }

    return V[n];
}

int main() {
    int coins[] = {5, 1, 2, 10, 6, 2};  
    int n = sizeof(coins) / sizeof(coins[0]); 

    int max_value = coin_row_problem(coins, n); 
    printf("Solução ótima: %d\n", max_value);

    return 0;
}
