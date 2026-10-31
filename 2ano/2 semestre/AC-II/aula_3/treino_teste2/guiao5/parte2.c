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

int main(void)
{
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	TRISBbits.TRISB0 = 1;
	TRISCbits.TRISC14 = 0;
	
	
	int counter = 0;
	int i, wait;
	int led_timer=0;
	
	while (1)
	{
		if (PORTBbits.RB0 ==1){
			wait=20;
		}
		else{
			wait=50;
		}
		i = 0;
		do
		{
			unsigned char bcd_value= toBcd(counter);
			send2displays(bcd_value);
		
		if (led_timer>0){
			LATCbits.LATC14= 1;
			led_timer--;
		}
		else{
			LATCbits.LATC14= 0;
		}
			
			resetCoreTimer();
			while (readCoreTimer()<200000);
		}while (++i<wait);
		
		if (PORTBbits.RB0 == 0){

			counter++;
		}
		else{

			counter--;
		}
		
		if (counter>=60){
			counter=0;
			led_timer=500;
			
		}
		else if (counter <0){
			counter= 59;
			led_timer=500;
		}

	}
	return 0;
	
}
