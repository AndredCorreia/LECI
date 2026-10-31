#include <detpic32.h>

int main (void)
{
	TRISDbits.TRISD3 = 0;
	TRISBbits.TRISB1= 1;
	
	T3CONbits.TCKPS = 2;
	PR3= 38461;
	TMR3= 0;
	T3CONbits.TON = 1;
	
	OC4CONbits.OCM=6;
	OC4CONbits.OCTSEL=1;
	OC4RS= 19231;
	OC4CONbits.ON = 1;
	
	int toggle =0;
	while(1)
	{
		resetCoreTimer();
		while (readCoreTimer()<26000000);
		if (PORTBbits.RB1==0)
		{
			
			if (toggle ==0)
			{
				OC4RS = 9615;
				toggle=1;
			}
			else
			{
				OC4RS = 28846;
				toggle = 0;
			}
		}
	}	
	return 0;	
}
