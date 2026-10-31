#include <detpic32.h>

volatile unsigned char bcdTemp = 0; 


unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value) {
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; 

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;

    if (displayFlag == 0) {
        LATDbits.LATD5 = 1; // Ativa display Low
        LATDbits.LATD6 = 0; // Desativa display High
        LATB = (LATB & 0x80FF) | ((int)display7Scodes[digit_low] << 8);
    } else {
        LATDbits.LATD5 = 0; // Desativa display Low
        LATDbits.LATD6 = 1; // Ativa display High
        LATB = (LATB & 0x80FF) | ((int)(display7Scodes[digit_high] | 0x80) << 8);
    }
    displayFlag = !displayFlag;
}

void _int_(12) isr_T3 (void)
{
	send2displays(bcdTemp);
	IFS0bits.T3IF=0;
}

int main(void)
{
	TRISD = TRISD & 0xFF9F;
	TRISB = TRISB & 0x80FF;
	//ADC CONFIGURATION
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC= 7;
	
	AD1CON1bits.CLRASAM = 1;
 	AD1CON3bits.SAMC = 16; 
 	AD1CON2bits.SMPI = 1; 

 	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;
	
	//Configuracao do T3
	T3CONbits.TCKPS= 1;
	PR3 = 39999;
	TMR3= 0;
	T3CONbits.TON= 1;
	
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE= 1;
	IFS0bits.T3IF = 0;
	
	EnableInterrupts();
	
	
	
	
	while(1)
	{
		resetCoreTimer();
		while (readCoreTimer() < 4000000);
		
		AD1CON1bits.ASAM = 1;
		
		while( IFS1bits.AD1IF == 0 );
		
		int media = (ADC1BUF0 + ADC1BUF1)/2;
		int temperatura = ((media*66+511)/1023)+7;
		bcdTemp= toBcd(temperatura);
		
		IFS1bits.AD1IF= 0;
	}
	return 0;
	
}
		
