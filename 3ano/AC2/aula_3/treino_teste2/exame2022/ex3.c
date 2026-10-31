#include <detpic32.h>

volatile int contador=15;
void putc(char byte)
{
	while (U2STAbits.UTXBF==1);
	U2TXREG= byte;
}
void putstr (char *str)
{
	while (*str != '\0')
	{
		putc(*str);
		str++;
	}
}
void _int_(32) isr_UART2(void)
{
	if (IFS1bits.U2RXIF==1)
	{
		char c = U2RXREG;
		if (c=='U')
		{
			contador++;
			if (contador>15)
			{
				contador=0;
			}

		}
		if (c=='R')
		{
			contador=0;
			putstr("RESET");
		}
		LATE= (LATE & 0xFFE1) | (contador<<1);
		IFS1bits.U2RXIF=0;
	}
			
					
}


int main (void)
{
	TRISE = TRISE & 0xFFE1;
	LATE = (LATE & 0XFFE1)|(contador<<1);
	//configuracao uart2
	U2BRG= 129;
	U2MODEbits.BRGH= 0;
	
	U2MODEbits.PDSEL= 2;
	U2MODEbits.STSEL= 1;
	
	U2STAbits.UTXEN= 1;
	U2STAbits.URXEN= 1;
	
	U2MODEbits.ON= 1;
	
	IPC8bits.U2IP= 2;
	IEC1bits.U2RXIE= 1;
	IEC1bits.U2TXIE = 0;
	IFS1bits.U2RXIF= 0;
	
	U2STAbits.URXISEL = 0;
	
	
	EnableInterrupts();
	while(1)
	{
		IdleMode();
	}
	return 0;
}
	
	
