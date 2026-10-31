#include <detpic32.h>

int main (void)
{
	//configuracao portas
	TRISBbits.TRISB0= 1;
	TRISBbits.TRISB3= 1;
	TRISDbits.TRISD1= 0;

	T2CONbits.TCKPS= 2;
	PR2= 33333;
	TMR2= 0;
	T2CONbits.TON= 1;
	
	OC2CONbits.OCM = 6;
	OC2CONbits.OCTSEL = 0;
	OC2RS= 8333;
	OC2CONbits.ON= 1;
	
	while(1)
	{
		resetCoreTimer();
		while (readCoreTimer()<5000);
		if (PORTBbits.RB0==1 && PORTBbits.RB3==0)
		{
			OC2RS= 8333;
		}
		else if (PORTBbits.RB0==0 && PORTBbits.RB3==1)
		{
			OC2RS= 23333;
		}
	}
	return 0;
	
}
