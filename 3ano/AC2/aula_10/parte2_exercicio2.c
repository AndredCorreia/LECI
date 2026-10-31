#include <detpic32.h>

void putc1(char byte) {
    while (U1STAbits.UTXBF == 1);
    U1TXREG = byte;
}

int main(void) {
    U1BRG = 10;
    U1MODEbits.BRGH = 0;

    U1MODEbits.PDSEL = 1;
    U1MODEbits.STSEL = 0;

    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    U1MODEbits.ON = 1;

    while(1) {
        putc1(0x5A);
        resetCoreTimer();
        while(readCoreTimer() < 200000);
    }
    return 0;
}
