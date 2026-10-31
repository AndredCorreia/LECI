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
} 

void _int_(32) isr_uart2(void) { // Usando o vetor 32 para o PIC32
    // if (UART2 Tx interrupt flag is set) [cite: 100]
    if (IFS1bits.U2TXIF == 1) {
        
        // At least one character to be transmitted [cite: 103]
        if (txbuf.nchar > 0) { // [cite: 102]
            // Read 1 character from the buffer and send it [cite: 103, 104]
            U2TXREG = txbuf.mem[txbuf.posrd]; // Coloca no buffer de transmissão da UART 
            
            // Update buffer "posrd" and "nchar" variables [cite: 105]
            txbuf.posrd++;
            txbuf.nchar--;
        } else {
            // Disable UART2 Tx interrupts 
            // Quando já não há caracteres, desligamos a interrupção para ela parar de ser chamada
            IEC1bits.U2TXIE = 0; 
        }
        
        // Clear UART2 Tx interrupt flag 
        IFS1bits.U2TXIF = 0;
    }
}

int main(void) {
    // 1. Configurar a UART2: 115200 baudrate, N, 8, 1 [cite: 119]
    // Assumindo PBCLK de 20MHz
    U2BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
    U2MODEbits.BRGH = 0;  // Divisor de 16
    U2MODEbits.PDSEL = 0; // 8 bits, sem paridade
    U2MODEbits.STSEL = 0; // 1 stop bit
    U2STAbits.UTXEN = 1;  // Ativa a transmissão
    U2STAbits.URXEN = 1;  // Ativa a receção
    U2MODEbits.ON = 1;    // Liga o módulo UART2

    // 2. Configurar as interrupções da UART2 [cite: 120]
    // Inicialmente, as interrupções de RX e TX começam DESATIVADAS [cite: 120-121]
    IEC1bits.U2RXIE = 0; 
    IEC1bits.U2TXIE = 0; 
    
    // Configurar o nível de prioridade da UART2 no registo IPC8 [cite: 124]
    IPC8bits.U2IP = 2;   // Exemplo: prioridade nível 2
    
    // Limpar a flag de interrupção de TX preventivamente
    IFS1bits.U2TXIF = 0;

    // Definir o modo de interrupção de TX (bits UTXISEL) [cite: 126]
    // Modo 00: Gera interrupção quando o FIFO de transmissão tem pelo menos 1 posição livre [cite: 9, 12]
    U2STAbits.UTXISEL = 0; 

    // 3. Ativar as interrupções globais do sistema [cite: 127]
    EnableInterrupts();

    // 4. Inicializar a variável do buffer "nchar" a 0 [cite: 128]
    txbuf.nchar = 0;

    // Ciclo infinito de teste [cite: 129]
    while (1) {
        putstrInt("Test string which can be as long as you like, up to a maximum of 100 characters\n"); 
    }
    
    return 0;
}
