#include <detpic32.h>

void send2displays (unsigned char value)
{
	static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag= 0;
	
	int digit_low = value & 0x0F;
	int digit_high= value >>4;
	
	if (displayFlag ==0)
	{
		LATDbits.LATD5 = 1;
        	LATDbits.LATD6 = 0;
		LATB = (LATB & 0x80FF)| (disp7Scodes[digit_low] <<8);

		
	}
	else{
		LATDbits.LATD5 = 0;
        	LATDbits.LATD6 = 1;
		LATB = (LATB & 0x80FF)| (disp7Scodes[digit_high] <<8);

	}
	displayFlag= !displayFlag;
}

unsigned char toBcd(unsigned char value)
{
	return ((value /10) <<4) + (value %10);
}

int main (void)
{
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC= 16;
	AD1CON2bits.SMPI = 3;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON= 1;
	
	
	int i=0;
	unsigned char voltage_bcd=0;
	
	while(1)
	{
		if (i==0)
		{
			AD1CON1bits.ASAM =1;		//start conversion
		
			while( IFS1bits.AD1IF == 0);
			
			int *p = (int *)(&ADC1BUF0);
            		int j, soma = 0;
            
           		for(j = 0; j < 4; j++) 
            		{
                		soma += p[j * 4]; 
            		}
            		
            		
            		int media= soma/4;
            		int tensao= (media* 33+511)/1023;
            		
            		voltage_bcd= toBcd(tensao);
            		IFS1bits.AD1IF=0;
            		
            	}
            	send2displays(voltage_bcd);
            	
            	resetCoreTimer();
            	while (readCoreTimer()<200000);
            	i= (i+1)%20;			
        }
        return 0;
        
}
