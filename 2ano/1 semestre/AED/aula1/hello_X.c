#include <stdio.h>

int main() {
    char nome[50];
    char apelido[50];

    printf("Digite seu nome (usando gets): ");
    scanf(nome);  // gets() lê a entrada até encontrar uma nova linha, mas pode causar overflow
    printf("Introduza o seu apelido: ");
    scanf(apelido);
    printf("Olá %s!\n", nome);

    
}
