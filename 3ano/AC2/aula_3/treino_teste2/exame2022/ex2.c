#include <detpic32.h>

unsigned char temperaturaBcd;
unsigned char toBcd (unsigned char valor)
{
	return ((valor/10)<<4) + (valor%10);
}
void send2displays( unsigned char value){
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;
	
	unsigned char digit_low = value & 0x0F;
    	unsigned char digit_high = value >> 4;

	
	if (displayFlag==0)
	{
		LATDbits.LATD5= 1;
		LATDbits.LATD6=0;
		LATB= ((LATB & 0x80FF) | display7Scodes[digit_low]<<8);
	}
	else 
	{
		LATDbits.LATD5= 0;
		LATDbits.LATD6=1;
		LATB= ((LATB & 0x80FF) | (display7Scodes[digit_high]|0x80)<<8);
	}
	displayFlag= !displayFlag;
}

void _int_(8) isr_T2 (void)
{	
	send2displays(temperaturaBcd);
	IFS0bits.T2IF=0;
}
int main (void)
{
	TRISB= TRISB & 0x80FF;
	TRISD= TRISD & 0xFF9F;
	TRISBbits.TRISB4= 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC = 7;
	
	AD1CON1bits.CLRASAM = 1;
	
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI= 1;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON= 1;
	
	T2CONbits.TCKPS = 2;
 	PR2 = 41666;
 	TMR2 = 0; 
 	T2CONbits.TON = 1; 
 	
 	IPC2bits.T2IP= 2;
 	IEC0bits.T2IE= 1;
 	IFS0bits.T2IF= 0;
 	
 	EnableInterrupts();
	
	while(1)
	{	
		resetCoreTimer();
		while (readCoreTimer()<2000000);
		
		AD1CON1bits.ASAM=1;
		
		while (IFS1bits.AD1IF==0);
		
		int media= (ADC1BUF0 + ADC1BUF1)/2;
		int temperatura= ((media*50 +511)/1023)+15;
		temperaturaBcd= toBcd(temperatura);
		
		IFS1bits.AD1IF=0;
	}
	return 0;
	
	
}
