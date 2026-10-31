#include <detpic32.h>
	
int main(void)
{
	//Portas entrada e saida
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB2 = 1;
	TRISDbits.TRISD1= 0;
	
	
	//Configuracao TIMER3
	T3CONbits.TCKPS = 2;
	PR3 = 41667;
	TMR3=0;
	T3CONbits.TON=1;
	
	
	//PWM
	OC2CONbits.OCM =6;
	OC2CONbits.OCTSEL = 1;
	OC2RS = 31250;
	OC2CONbits.ON =1;
	
	while(1)
	{
		resetCoreTimer();
		while (readCoreTimer()<7200);
		if (PORTBbits.RB0 ==0 && PORTBbits.RB2==0)
		{
			OC2RS= 12500;
		}
		else if (PORTBbits.RB0==1 && PORTBbits.RB2==1)
		{
			OC2RS= 22917;
		}
		else 
		{	

		}

		
	}
	return 0;
	
}
