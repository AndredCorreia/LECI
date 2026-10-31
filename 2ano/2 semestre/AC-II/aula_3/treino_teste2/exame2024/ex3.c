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

void _int_(32) isr_UART2(void)
{
	if (IFS1bits.U2RXIF==1)
	{
		char valor = U2RXREG;
		LATEbits.LATE7 = !LATEbits.LATE7;
		putc(valor);
		putc('\n');
		
		
		if (valor == 'D'){
			
			putstr("DSD=");
			int sw = PORTB & 0x000F;
			
			if (sw>=10)
			{
				putc('1');
				putc((sw-10)+'0');
			}
			else {
				putc(sw + '0');
			}
			putc('\n');	
		}
		IFS1bits.U2RXIF =0;
	}
}
		
		
int main (void)
{
	//Configuracao UART2
	U2BRG = 129;
	U2MODEbits.BRGH= 0;
	
	U2MODEbits.PDSEL= 2;
	U2MODEbits.STSEL= 1;
	
	U2STAbits.UTXEN= 1;
	U2STAbits.URXEN= 1;
	
	U2MODEbits.ON = 1;
	
	IPC8bits.U2IP = 2;
	IEC1bits.U2RXIE=1;
	IEC1bits.U2TXIE = 0;
	IFS1bits.U2RXIF=0;
	
	
	
	//Configuracao portos entrada e saida
	TRISB = TRISB | 0x000F;
	TRISEbits.TRISE7 = 0;
	LATEbits.LATE7 =0;
	

	EnableInterrupts();
	
	while(1)
	{
		IdleMode();
	}
	return 0;
	
		
}
