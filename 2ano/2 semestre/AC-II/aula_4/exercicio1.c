#include <detpic32.h>

 int main(void)
 {
 	// Configure port RC14 as output -> TRISCbits.TRISC14 = 0; OU TRISC= TRISC & 0xBFFF
 	TRISCbits.TRISC14=0;
 	while(1)
 	{
 		// Wait 0.5s-> delay(500ms) ou resetCoreTimer();while(readCoreTimer<20000000/2);
 		resetCoreTimer();
 		while(readCoreTimer() < 10000000);
 		LATCbits.LATC14= !LATCbits.LATC14; // Toggle RC14 port value
 		
 	}
 return 0;
 }
