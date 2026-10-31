#include <detpic32.h>

int main (void)
{
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC= 16;
	AD1CON2bits.SMPI = 3;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON= 1;
	

	
	while(1)
	{
		AD1CON1bits.ASAM =1;		//start conversion
		
		while( IFS1bits.AD1IF == 0);	//wait while conversion not done
		
		int *p = (int *)(&ADC1BUF0);
		int i, sum=0, average, v;
		for (i=0;i<4;i++)
		{
			sum += p[i*4];
		}
		average = sum/4;
		v= (average * 33 + 511)/1023;
		printStr("Tensao: ");
		printInt(v, 10 | 2<<16);
		printStr("\r");
		
		IFS1bits.AD1IF = 0;
		
	}
	return 0;
	
}

