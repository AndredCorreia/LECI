#include <detpic32.h>


void putc (char byte)
{
	while (U2STAbits.UTXBF ==1);
	U2TXREG = byte;
}

void putstr(char *str)
{
	
	while (*str != '\0')
	{
		putc (*str);
		str++;
	}
	
}


int main (void)
{
	//Configure Baudrate Generator
	U2BRG = 10;
	U2MODEbits.BRGH = 0;
	
	//Configure number of data bits, parity and number of stop bits
 	// (see U2MODE register)
 	 
	U2MODEbits.PDSEL = 0; //8 databits, sem paridade (N)->0, impar(O)->1, par(E)->2
	U2MODEbits.STSEL = 0; // stopbit (0->1; 1->2)
 	
	//Enable the trasmitter and receiver modules (see register U2STA)
	U2STAbits.UTXEN = 1;
	U2STAbits.URXEN = 1;
	
	
	//Enable UART
	U2MODEbits.ON =1;
	
	while(1)
	{
		putstr("String de teste\n");
		resetCoreTimer();
		while (readCoreTimer()<20000000);
	}
	return 0;
}	

