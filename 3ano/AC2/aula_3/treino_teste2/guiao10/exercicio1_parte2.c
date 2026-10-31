#include <detpic32.h>


void put1c (char byte)
{
	while (U1STAbits.UTXBF ==1);
	U1TXREG = byte;
}



int main (void)
{
	//Configure Baudrate Generator
	U1BRG = 10;
	U1MODEbits.BRGH = 0;
	
	//Configure number of data bits, parity and number of stop bits
 	// (see U2MODE register)
 	 
	U1MODEbits.PDSEL = 2; //8 databits, sem paridade (N)->0, impar(O)->1, par(E)->2
	U1MODEbits.STSEL = 0; // stopbit (0->1; 1->2)
 	
	//Enable the trasmitter and receiver modules (see register U2STA)
	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;
	
	
	//Enable UART
	U1MODEbits.ON =1;
	
	while(1)
	{
		put1c(0x5A);
		resetCoreTimer();
		while (readCoreTimer()<4000000);

			
	}
	return 0;
}	

