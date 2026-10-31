#include <detpic32.h>


typedef struct
{
	char mem[101];
	int nchar;
	int posrd;
} t_buf;

volatile t_buf txbuf;

void putstrInt (char *s)
{
	while (txbuf.nchar >0);
	
	int i=0;
	while (*s !=0){
		txbuf.mem[i] = *s;
		s++;
		i++;
	}
	
	txbuf.nchar = i;
	txbuf.posrd = 0;
	IEC1bits.U2TXIE = 1;
}

void _int_(32) isr_uart2(void)
{
	if (U2STAbits.UTXEN == 1)
	{
		if (txbuf.nchar>0)
		{
			U2TXREG = txbuf.mem[txbuf.posrd];
			txbuf.posrd++;
			txbuf.nchar--;
		} else {
			IEC1bits.U2TXIE = 0;
		}
		IFS1bits.U2TXIF=0;
	}
}
	
int main (void)
{
	U2BRG=10;
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL = 0;
	U2MODEbits.STSEL = 0;
	
	
	U2STAbits.UTXEN =1;
	U2STAbits.URXEN =1;
	U2MODEbits.ON=1;
	
	IPC8bits.U2IP = 2;
	IEC1bits.U2TXIE=0;
	IEC1bits.U2RXIE =0;
	U2STAbits.UTXISEL =1;
	
	EnableInterrupts();
	
	txbuf.nchar=0;
	while(1){
		resetCoreTimer();
		while (readCoreTimer()<10000000);
		putstrInt("VAMOS TER 20 A AC\n");
	}
	return 0;
	
}
	
