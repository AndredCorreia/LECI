#include <detpic32.h>

volatile unsigned char temperatura_bcd = 0;

void send2displays(unsigned char value) {
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; // Variável estática não perde o valor entre chamadas

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;

    // Alterna a cada chamada da função
    if (displayFlag == 0) {
        LATDbits.LATD6 = 0; // Desativa o display High
        LATDbits.LATD5 = 1; // Ativa o display Low
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_low] << 8); // Envia o dígito Low
    } else {
        LATDbits.LATD5 = 0; // Desativa o display Low
        LATDbits.LATD6 = 1; // Ativa o display High
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_high] << 8); // Envia o dígito High
    }
    
    displayFlag = !displayFlag; // Inverte a flag (0 passa a 1, 1 passa a 0)
}

void _int_(12) isr_T3(void)
{
    send2displays(temperatura_bcd);
    IFS0bits.T3IF = 0;
}

void delay(unsigned int ms) 
{
    // Para cada milissegundo pedido
    for (; ms > 0; ms--) {
        resetCoreTimer(); // Faz reset ao temporizador do processador
        // Espera até que o temporizador atinja 20000 (1 ms a 20 MHz)
        while (readCoreTimer() < 20000); 
    }
}


int main(void) 
{
    TRISD = TRISD & 0xFF9F; // RD5 e RD6 como saídas (seleção do display)
    TRISB = TRISB & 0x80FF; // RB8 a RB14 como saídas (segmentos)

    T3CONbits.TCKPS = 5;
    PR3 = 2231;
    TMR3 = 0;
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 1;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    EnableInterrupts();

    while(1)
    {
        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);

        int V_adc = (ADC1BUF0 + ADC1BUF1) / 2;
        IFS1bits.AD1IF = 0;

        unsigned char temp_decimal = 10 + ((V_adc * 65) / 1023);

        temperatura_bcd = ((temp_decimal / 10) << 4) | (temp_decimal % 10);
        
        delay(200);
        
    }
    return 0;
}






