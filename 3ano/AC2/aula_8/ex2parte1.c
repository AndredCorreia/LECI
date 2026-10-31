#include <detpic32.h>
int main(void){
 	// Configure Timer T3 with interrupts enabled
 	T3CONbits.TCKPS = 7;    
 	PR3 = 39062;            // 20.000.000/(256*2)-1 = 39.061,5
 	TMR3 = 0; 
 
 	IPC3bits.T3IP = 2;
 	IEC0bits.T3IE = 1;
 	IFS0bits.T3IF = 0;
 	
 	T3CONbits.TON = 1;
	EnableInterrupts();
	while(1){
	 	IdleMode(); // CPU enters Idle mode3 (CPU is halted,
	 	// but peripherals continue to operate)
	}
	return 0;
	}
	int count=0;
	void _int_(12) isr_T3(void){ // Replace VECTOR by the timer T3
	// vector number
		count++;
		if (count==2){
			putChar('.');
			count=0;
		}
	// Reset T3 interrupt flag
	 	IFS0bits.T3IF=0;
	}
