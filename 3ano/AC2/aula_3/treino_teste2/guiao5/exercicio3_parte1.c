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
int main(void)
{
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	
	while(1)
	{
		send2displays(0x15);
		resetCoreTimer();
		while (readCoreTimer()<20000000);
	}
	return 0;
}

