#include <stdio.h>
#include <math.h> // Necessário para sqrt()

int main() {
    int n;

    // Solicita ao usuário o número de linhas para a tabela
    printf("Digite o número de linhas para a tabela: ");
    scanf("%d", &n);

    // Imprime o cabeçalho da tabela
    printf("%-10s %-10s %-15s\n", "Número", "Quadrado", "Raiz Quadrada");

    // Gera a tabela com os números, seus quadrados e raízes quadradas
    for (int i = 1; i <= n; i++) {
        printf("%-10d %-10d %-15.2f\n", i, i * i, sqrt((double)i)); // Conversão para double
    }

    return 0;
}
