#include <detpic32.h>

int main (void)
{
	TRISEbits.TRISE0 = 0;
	TRISDbits.TRISD8 = 1;
	
	LATEbits.LATE0 = 0;
	
	
	T2CONbits.TCKPS = 5;
	PR2= 62499;
	TMR2=0;
	T2CONbits.TON = 0;
	
	IPC2bits.T2IP = 2;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;
	
	INTCONbits.INT1EP= 0;
	IPC1bits.INT1IP = 2;
	IEC0bits.INT1IE = 1;
	IFS0bits.INT1IF = 0;
	
	EnableInterrupts();
	while(1)
	{
		IdleMode();
	}
	return 0;	
}
volatile int soft_clk = 0;

void _int_(7) isr_INT1 (void)
{ 
	LATEbits.LATE0 = 1;
	soft_clk = 0;
	T2CONbits.TON = 1;
	
	IFS0bits.INT1IF = 0;

}
void _int_(8) isr_T2 (void)
{
	soft_clk++;
	if (soft_clk==30)
	{
		LATEbits.LATE0 =0;
		T2CONbits.TON = 0;
	}
	IFS0bits.T2IF = 0;
		
		
}


