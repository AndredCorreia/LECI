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
	
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB3 = 1;
	
	//timer T1
	T1CONbits.TCKPS = 2;
	PR1= 31249;
	TMR1= 0;
	T1CONbits.TON =1;
	
	IPC1bits.T1IP=2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF= 0;
	
	//timer T2
	T2CONbits.TCKPS = 2;
	PR2= 49999;
	TMR2= 0;
	T2CONbits.TON =1;
	
	IPC2bits.T2IP=1;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF= 0;
	
	EnableInterrupts();
	while (1)
	{
		IdleMode();
	}
	return 0;
	
}


volatile int dir = 0;
volatile int pause = 0;
volatile unsigned char counter =0;
volatile int soft_clk =0;
void _int_(8) isr_T2(void)
{
	dir= PORTBbits.RB0;
	pause = PORTBbits.RB3;
	send2displays(toBcd(counter));
	IFS0bits.T2IF = 0;
	
}	

void _int_(4) isr_T1(void)
{
	soft_clk++;
	if (soft_clk==10){
		soft_clk =0;
		
		if (pause==1)
		{
			if (dir==1)
			{
			counter ++;
			}
			else
			{
			counter--;
			}
		}	
		if (counter==30)
		{
			counter=0;
		}
		if (counter== 255)
		{
			counter=29;
		}
	}
	IFS0bits.T1IF = 0;
}


