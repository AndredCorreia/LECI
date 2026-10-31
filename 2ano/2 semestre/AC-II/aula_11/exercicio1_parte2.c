#include <detpic32.h>

// 1. Declaração da estrutura do buffer temporário [cite: 73, 74, 76, 77, 80, 81, 82]
typedef struct {
    char mem[100]; // Área de armazenamento dos caracteres [cite: 77]
    int nchar;     // Número de caracteres que ainda faltam transmitir [cite: 78, 80]
    int posrd;     // Posição do próximo caracter a ser lido para transmissão [cite: 79, 81]
} t_buf;

// 2. Criação da instância global (fora de qualquer função) [cite: 83, 84]
volatile t_buf txbuf;

// --------------------------------------------------------
// EXERCÍCIO 1 (Parte II): Função putstrInt
// --------------------------------------------------------
void putstrInt(char *s) { // [cite: 87]
    // Espera passivamente enquanto o buffer não estiver vazio (transmissões anteriores) [cite: 90]
    while (txbuf.nchar > 0); 
    
    // Copia os caracteres da string "s" para o buffer e atualiza o "nchar" [cite: 91]
    int i = 0;
    while (s[i] != '\0') { // [cite: 92]
        txbuf.mem[i] = s[i]; // Copia o caracter para a memória do buffer [cite: 85]
        i++;
    } // [cite: 93]
    
    txbuf.nchar = i; // Atualiza o total de caracteres a transmitir 

    // Inicializa a variável "posrd" com 0 (vamos começar a ler do início do buffer) [cite: 94]
    txbuf.posrd = 0;

    // Ativa as interrupções de transmissão da UART2 
    IEC1bits.U2TXIE = 1; 
} // [cite: 89]
