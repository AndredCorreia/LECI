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
	
	int i,segment;
	
	while(1)
	{
		segment=1;
		for (i=0;i<7;i++)
		{
			LATB= (LATB & 0x80FF) | (segment << 8);
			resetCoreTimer();
			while (readCoreTimer()<10000000);
			segment= segment<<1;
		}
		LATDbits.LATD5 = !LATDbits.LATD5;
		LATDbits.LATD6 = !LATDbits.LATD6;
	}
	return(0);
	
}	
