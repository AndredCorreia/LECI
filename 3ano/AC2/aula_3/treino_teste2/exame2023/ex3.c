#include <detpic32.h>

volatile int contador=0;
void putc(char byte)
{
	while (U2STAbits.UTXBF==1);
	U2TXREG = byte;
}

void putstr(char *str)
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
		putc (c);
		if (c== 'F')
		{
			contador++;
			if (contador>9)
			{
				contador=0;
			}
			LATE =( LATE & 0xFFF0 )| contador;
		}
		else if (c == 'C')
		{
			contador=0;
			LATE =( LATE & 0xFFF0 )| contador;
			putstr("VALOR MINIMO");
		}
		IFS1bits.U2RXIF=0;	
	}
}
int main (void)
{
	TRISE = TRISE & 0xFFF0;
	LATE = LATE & 0xFFF0;
	
	//configuracao UART
	U2BRG= 520;
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL= 1;
	U2MODEbits.STSEL=1;
	
	
	U2STAbits.UTXEN= 1;
	U2STAbits.URXEN= 1;
	
	U2MODEbits.ON= 1;
	
	IPC8bits.U2IP= 2;
	IEC1bits.U2RXIE= 1;
	IEC1bits.U2TXIE= 0;
	IFS1bits.U2RXIF= 0;
	

	EnableInterrupts();
	
	while(1)
	{
		IdleMode();
	}
	return 0;	
}
