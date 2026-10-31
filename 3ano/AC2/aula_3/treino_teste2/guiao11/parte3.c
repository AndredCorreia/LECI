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

void send2displays (unsigned char value)
{
	static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag= 0;
	
	int digit_low = value & 0x0F;
	int digit_high= value >>4;
	
	if (displayFlag ==0)
	{
		LATDbits.LATD5 = 1;
        	LATDbits.LATD6 = 0;
		LATB = (LATB & 0x80FF)| (disp7Scodes[digit_low] <<8);

		
	}
	else{
		LATDbits.LATD5 = 0;
        	LATDbits.LATD6 = 1;
		LATB = (LATB & 0x80FF)| (disp7Scodes[digit_high] <<8);

	}
	displayFlag= !displayFlag;
}

unsigned char toBcd(unsigned char value)
{
	return ((value /10) <<4) + (value %10);
}

volatile int voltage,voltMax= 0;
volatile int voltMin = 33;

void _int_(4) isr_T1 (void)
{
	AD1CON1bits.ASAM =1; 		//start conversion
	IFS0bits.T1IF = 0;		//reset T1IF flag 
}

void _int_(12) isr_T3 (void)
{
	send2displays (toBcd(voltage));
	IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void)
{
	int soma, media;
	soma= ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3;
	media= soma/4;
	
	voltage = (media * 33 +511)/1023;
	if (voltage>voltMax)
	{
		voltMax=voltage;
	}
	if (voltage<voltMin)
	{
		voltMin=voltage;
	}	
		
	IFS1bits.AD1IF = 0;
}
int status = 1;
void _int_(32) isr_uart2(void)
{
	char c = U2RXREG;

	if (c == 'M')
	{
		putstr("VMAX=");
		unsigned char bcd= toBcd(voltMax);
		putc ((bcd>>4)+'0');
		
		putc('.');
		putc ((bcd & 0x0F) + '0');
		putstr("V\n");	
	}
	else if (c=='m')
	{
		putstr("VMIN=");
		unsigned char bcd= toBcd(voltMin);
		putc ((bcd>>4)+'0');
		
		putc('.');
		putc ((bcd & 0x0F) + '0');
		putstr("V\n");	
	}
	else if (c=='P')
	{
		IEC0bits.T1IE=0;
		status = 0;
	}
	else if (c=='R')
	{
		IEC0bits.T1IE=1;
		status = 1;
	}
	else if (c=='S')
	{
		if (status==0){
			putstr("ADC INATIVA\n");
		}
		else {
			putstr("ADC ATIVA\n");
		}
	}
	
	IFS1bits.U2RXIF = 0;
}

int main (void)
{
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	
	//Timer T1
	T1CONbits.TCKPS = 2;
	PR1= 62499;
	TMR1= 0;
	T1CONbits.TON =1 ;
	IPC1bits.T1IP = 2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	
	//Timer T3
	T3CONbits.TCKPS = 2;
	PR3= 49999;
	TMR3= 0;
	T3CONbits.TON =1 ;
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	
	
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC= 16;
	AD1CON2bits.SMPI = 3;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON= 1;
	
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	
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
	
	
	EnableInterrupts();
	while(1)
	{
		IdleMode();				
        }
        return 0;
        
}


