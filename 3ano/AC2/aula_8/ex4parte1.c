#include <detpic32.h>
int main(void){
 // Configure Timers T1 and T3 with interrupts enabled)
 	T3CONbits.TCKPS = 6;    
 	PR3 = 12499;            // 20.000.000/(64*25)-1 = 12499
 	TMR3 = 0; 
 
 	IPC3bits.T3IP = 2;
 	IEC0bits.T3IE = 1;
 	IFS0bits.T3IF = 0;
 	
 	T3CONbits.TON = 1;
 	
 	T1CONbits.TCKPS = 2;
 	PR1 = 62499;
 	TMR1 = 0;
 	IPC1bits.T1IP = 2;
 	IEC0bits.T1IE = 1;
 	IFS0bits.T1IF = 0;
 	 	
 	T1CONbits.TON = 1;
 	
 	
 	
 	
 
 
 	// Reset T1IF and T3IF flags
 	EnableInterrupts(); // Global Interrupt Enable
 	while(1) {
 		IdleMode();
 	}
 	return 0;
 	}
 	
 	void _int_(4) isr_T1(void){
	// print character '1'
		putChar('1');
		IFS0bits.T1IF=0;
 	// Reset T1IF flag
 	}
 	
 	void _int_(12) isr_T3(void){
 	// print character '3'
 		putChar('3');
 		IFS0bits.T3IF=0;
 	// Reset T3IF flag
 	} 
