#include <detpic32.h>

int main(void)
{
	TRISBbits.TRISB8 = 0;
	TRISBbits.TRISB9 = 0;
	TRISBbits.TRISB10 = 0;
	TRISBbits.TRISB11 = 0;
	TRISBbits.TRISB12 = 0;
	TRISBbits.TRISB13 = 0;
	TRISBbits.TRISB14 = 0;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	LATDbits.LATD5=1;
	LATDbits.LATD6=0;
	
	char ch;
	
	while(1)
	{
		ch= getChar();
		
		if (ch>='a' && ch<='g'){
			ch= ch-'a';
			LATB= (LATB & 0x80FF) | 1 << (ch + 8);
		}
		

	}
	return(0);
	
}	
