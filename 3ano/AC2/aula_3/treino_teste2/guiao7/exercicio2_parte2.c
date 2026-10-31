#include <detpic32.h>

void _int_(27) isr_adc(void)
{
	//printInt(ADC1BUF0, 16 | 3 <<16);
	//printStr("\r");
	LATDbits.LATD11 = 0;	//reset RD11
	int volatile adc_value = ADC1BUF0;

	
	AD1CON1bits.ASAM= 1;	//Start conversion
	IFS1bits.AD1IF = 0;	//reset AD1IF flag
	LATDbits.LATD11 = 1;	//set RD11
}

int main (void)
{
	//Configure AD module
	TRISDbits.TRISD11= 0;
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC= 16;
	AD1CON2bits.SMPI = 0;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON= 1;
	
	//Configure interrupt system
	IFS1bits.AD1IF = 0;
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	
	EnableInterrupts();	//Enable a interrupcao
	AD1CON1bits.ASAM= 1;	//Start conversion
	
	while(1)
	{
		LATDbits.LATD11 = 0;	//reset RD11
	}	
	return 0;
	
}

	
	
