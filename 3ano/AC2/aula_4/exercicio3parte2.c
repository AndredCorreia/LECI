#include <detpic32.h>

int main(void){
	unsigned char segment;

 	 // configure RD5-RD6 as outputs
 	TRISDbits.TRISD5 = 0;
    	TRISDbits.TRISD6 = 0;
	 // enable display low (RD5) and disable display high (RD6)
    	LATDbits.LATD5 = 1;
    	LATDbits.LATD6 = 0;

 	// configure RB8-RB14 as outputs
 	TRISB= TRISB & 0x80FF;

 	while(1)
 	{
 		segment = 1;
 		int i=0;
		for(i=0;i<7;i++){
 			// send "segment" value to display
 			LATB= (LATB& 0x80FF) | (segment <<8);
 			// wait 0.5 second
 			resetCoreTimer();
 			while(readCoreTimer() < 400000); //change to 200000->10Hz;100000->50Hz;20000->100Hz
 			segment = segment << 1;
 		}
 		// toggle display selection
 		LATDbits.LATD5 = !LATDbits.LATD5;
        	LATDbits.LATD6 = !LATDbits.LATD6;
 	}
 	return 0;
 } 
