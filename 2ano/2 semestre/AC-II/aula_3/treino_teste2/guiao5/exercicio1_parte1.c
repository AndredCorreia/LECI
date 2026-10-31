#include <detpic32.h>

void send2displays (unsigned char value)
{
	static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	int dh, dl;
	
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;
	
	dh = value>>4;
	LATB = (LATB & 0x80FF) | (disp7Scodes[dh] << 8);
	
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 0;
	
	dl = value & 0x0F;
	LATB = (LATB & 0x80FF)| (disp7Scodes[dl] << 8) ;
	
}

int main(void)
{
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	
	while(1)
	{
		send2displays(0x15);
		resetCoreTimer();
		while (readCoreTimer()<4000000);
	}

}


