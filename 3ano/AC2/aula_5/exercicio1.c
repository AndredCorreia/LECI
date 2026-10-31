#include <detpic32.h> // Ou a biblioteca específica do seu simulador/placa

void send2displays(unsigned char value)
{
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; // Alterna entre 0 e 1

    unsigned char dl = value & 0x0F;
    unsigned char dh = value >> 4;

    if (displayFlag == 0) {
        LATDbits.LATD6 = 0;           // Desliga High
        LATDbits.LATD5 = 1;           // Liga Low
        LATB = (LATB & 0x80FF) | (disp7Scodes[dl] << 8);
    } else {
        LATDbits.LATD5 = 0;           // Desliga Low
        LATDbits.LATD6 = 1;           // Liga High
        LATB = (LATB & 0x80FF) | (disp7Scodes[dh] << 8);
    }
    
    displayFlag = !displayFlag; // Inverte para a próxima chamada
}


void delay( unsigned int ms){  
	for (;ms>0;ms--){
        	resetCoreTimer();
        	while(readCoreTimer() < 20000); // Exemplo para 20MHz (0.2s)
        }
    
}
int main(void)
{
    // 1. Configurar RB8-RB14 como saídas (Segmentos A-G)
    // TRISB = TRISB & 0x80FF; // Limpa bits 8 a 14 (0 = saída)
    TRISBbits.TRISB8  = 0;
    TRISBbits.TRISB9  = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;

    // 2. Configurar RD5 e RD6 como saídas (Seleção Display High/Low)
    TRISDbits.TRISD5 = 0; // Display Low (exemplo)
    TRISDbits.TRISD6 = 0; // Display High (exemplo)

    while(1)
    {
        // Envia o valor 0x15 (Dígito 1 no High, Dígito 5 no Low)
        send2displays(0x15);
        delay(200);
    }
    
    return 0;
}
