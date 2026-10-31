#include <detpic32.h>

void putc(char byte) {
    while (U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

char getc(void) {
    if (U2STAbits.OERR == 1) {
        U2STAbits.OERR = 0;
    }
    while (U2STAbits.URXDA == 0);
    return U2RXREG;
}

int main(void) {
    U2BRG = 10;
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    while (1) {
        char c = getc();
        putc(c);
    }
    return 0;
}
