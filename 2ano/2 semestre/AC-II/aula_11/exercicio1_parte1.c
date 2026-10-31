#include <detpic32.h>

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
