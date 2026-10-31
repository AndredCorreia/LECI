#include <detpic32.h>

void _int_(32) isr_uart2(void) {
    // Verifica se a flag de interrupção de receção (RX) está a 1
    if (IFS1bits.U2RXIF == 1) {
        
        // 1. Lê o caracter recebido do buffer (FIFO)
        char c = U2RXREG;
        
        // 2. Retransmite o mesmo caracter para o terminal (eco)
        putChar(c);
        printStr("\n");

        // 3. Se for recebido o carater '?', transmite a string por polling
        if (c == '?') {
            printStr("AC2-Guiao 11\n"); 
        }


        if (c == 'T') {
            LATCbits.LATC14 = 1; // Acende o LED se for a barra de espaço
        } else if (c == 't') {
            LATCbits.LATC14 = 0; // Apaga o LED se for a letra 't'
        }
        
        // 4. Limpa a flag de interrupção para não criar um ciclo infinito
        IFS1bits.U2RXIF = 0;
    }
}

int main(void) {
    // Configure UART2: 115200, N, 8, 1
    // Assumindo um relógio periférico (PBCLK) de 20MHz (padrão detpic32)
    U2BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
    U2MODEbits.BRGH = 0;  // Divisor 16
    U2MODEbits.PDSEL = 0; // 8 bits, no parity
    U2MODEbits.STSEL = 0; // 1 stop bit
    U2STAbits.UTXEN = 1;  // Enable TX
    U2STAbits.URXEN = 1;  // Enable RX
    U2MODEbits.ON = 1;    // Enable UART2

    // Configure UART2 interrupts, with RX interrupts enabled
    // and TX interrupts disabled:
    IEC1bits.U2RXIE = 1; // enable U2RXIE
    IEC1bits.U2TXIE = 0; // disable U2TXIE (register IEC1)
    
    IPC8bits.U2IP = 2;   // set UART2 priority level (register IPC8) - Exemplo: prioridade 2
    IFS1bits.U2RXIF = 0; // clear Interrupt Flag bit U2RXIF (register IFS1)
    
    // define RX interrupt mode (URXISEL bits)
    U2STAbits.URXISEL = 0; // Interrupção quando recebe pelo menos 1 carater

    // Enable global Interrupts
    EnableInterrupts();

    while (1) {
        IdleMode(); // Poupança de energia enquanto espera pela interrupção
    }
    
    return 0;
    
    
}
