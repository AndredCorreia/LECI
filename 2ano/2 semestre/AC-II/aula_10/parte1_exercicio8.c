#include <detpic32.h>

void putc(char byte) {
    while (U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

int main(void) {
    U2BRG = 10;
    U2MODEbits.BRGH = 0;

    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;

    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;

    U2MODEbits.ON = 1;

    int counter = 0;

    while (1) {
        int val = counter % 10;
        int i;
        
        for (i = 3; i >= 0; i--) {
            if (val & (1 << i)) {
                putc('1');
            } else {
                putc('0');
            }
        }
        putc('\n');

        counter++;

        resetCoreTimer();
        while(readCoreTimer() < 4000000);
    }
    return 0;
}
