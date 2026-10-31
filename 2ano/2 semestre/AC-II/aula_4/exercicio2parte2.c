#include <detpic32.h>

int main(void) {
    // TRISB: Bits 8 a 14 como saídas (0). 0x80FF 
    TRISB = TRISB & 0x80FF; 
    
    // TRISD: RD5 e RD6 como saídas para controlo dos displays
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    char ch;

    while(1) {
        ch = getChar();


        if(ch >= 'a' && ch <= 'g') {
 		ch = ch - 'a';
 		LATB = (LATB & 0x80FF);
 	
        	LATB = LATB | (1 << (ch + 8));
        }
    }

    return 0;
}
