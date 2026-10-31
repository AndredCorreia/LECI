#include <detpic32.h>

int main(void)
{
	TRISEbits.TRISE3 = 0;
	TRISEbits.TRISE4 = 0;	
	TRISEbits.TRISE5 = 0;	
	TRISEbits.TRISE6 = 0;		
	
	int counter= 0;
	int step =1 ;
	
	while(1){
	LATE = (LATE & 0xFF87) | counter <<3;
	
	resetCoreTimer();
	while (readCoreTimer()<4347826);
	counter = (counter + step) %10;
	}
	return 0;
	
	
}
