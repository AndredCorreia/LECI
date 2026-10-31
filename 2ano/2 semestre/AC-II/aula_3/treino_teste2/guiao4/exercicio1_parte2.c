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
		LATB = LATB & 0x80FF;
		
		if(ch == 'a') LATB = LATB | (1 << 8);  // Segmento A -> RB8
	        if(ch == 'b') LATB = LATB | (1 << 9);  // Segmento B -> RB9
	        if(ch == 'c') LATB = LATB | (1 << 10); // Segmento C -> RB10
	        if(ch == 'd') LATB = LATB | (1 << 11); // Segmento D -> RB11
	        if(ch == 'e') LATB = LATB | (1 << 12); // Segmento E -> RB12
	        if(ch == 'f') LATB = LATB | (1 << 13); // Segmento F -> RB13
	        if(ch == 'g') LATB = LATB | (1 << 14); // Segmento G -> RB14
		}
	}
	return(0);
	
}
		
