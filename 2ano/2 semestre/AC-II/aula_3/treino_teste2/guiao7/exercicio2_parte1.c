#include <detpic32.h>

volatile unsigned char voltage = 0;

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
    return ((value / 10) << 4) + (value % 10);
}

void _int_(27) isr_adc(void)
{
    int i, soma = 0, average, amplitude;
    int *p = (int *)(&ADC1BUF0); // Ponteiro para ler os 8 registos facilmente
    
    // 1. Somar as 8 amostras
    for(i = 0; i < 8; i++) 
    {
        soma += p[i * 4];
    }
    
    // 2. Calcular a média
    average = soma / 8;
    
    // 3. Calcular a amplitude da tensão (0 a 33)
    amplitude = (average * 33 + 511) / 1023;
    
    // 4. Converter para BCD e guardar na variável global
    voltage = toBcd(amplitude);
    
    // 5. Limpar a flag da interrupção
    IFS1bits.AD1IF = 0;    
}
int main (void)
{
	unsigned int cnt = 0;
	
	//Configure AD module
	TRISB = TRISB & 0x80FF;
	TRISD = TRISD & 0XFF9F;
	
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4= 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC= 16;
	AD1CON2bits.SMPI = 7;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON= 1;
	
	//Configure interrupt system
	IFS1bits.AD1IF = 0;
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	
	
	
	EnableInterrupts();
	while(1)
	{
		if (cnt==0)
		{
			AD1CON1bits.ASAM= 1;	//Start conversion
		}
		
		send2displays(voltage);
        
        	// 6. Matemática do temporizador: 200ms / 10ms = 20 voltas
        	cnt = (cnt + 1) % 20;
        
        	// 7. Esperar 10 ms (Frequência de 100 Hz para os displays não piscarem)
        	resetCoreTimer();
        	while (readCoreTimer() < 200000);
    	}
	return 0;
}


