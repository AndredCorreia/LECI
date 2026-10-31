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

void _int_(32) isr_uart2(void)
{
	if (IFS1bits.U2RXIF==1)
	{
		char car= U2RXREG;
		if (car == '?'){
			putstr("AC2-Guiao 11\n");
		}
		else if (car== 't')
		{
			LATCbits.LATC14 =0;
		}
		else if (car=='T')
		{
			LATCbits.LATC14=1;
		}
		else{
			putc(car);
			putc('\n');
		}
		IFS1bits.U2RXIF=0;
	}
}

int main(void)
{
	U2BRG= 10;
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL = 0;
	U2MODEbits.STSEL = 0;
	
	U2STAbits.UTXEN =1;
	U2STAbits.URXEN =1;
	
	U2MODEbits.ON = 1;
	
	IEC1bits.U2RXIE=1;
	IEC1bits.U2TXIE=0;
	
	IPC8bits.U2IP =2;
	IFS1bits.U2RXIF = 0;
	U2STAbits.URXISEL = 0;
	
	TRISCbits.TRISC14= 0;
	LATCbits.LATC14 =0;
	
	EnableInterrupts();
	
	while(1)
	{
		IdleMode();
	}
	return 0;
	
}
