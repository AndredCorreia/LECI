#include <detpic32.h>

//decimal to BCD
unsigned char toBcd(unsigned char value) 
{
    return ((value / 10) << 4) + (value % 10);
}

«
void send2displays(unsigned char value) 
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; 

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;

    if (displayFlag == 0) 
    {
        LATDbits.LATD5 = 1; // Ativa display Low
        LATDbits.LATD6 = 0; // Desativa display High
        // Envia o dígito menos significativo (casas decimais)
        LATB = (LATB & 0x80FF) | ((int)display7Scodes[digit_low] << 8);
    } 
    else 
    {
        LATDbits.LATD5 = 0; // Desativa display Low
        LATDbits.LATD6 = 1; // Ativa display High
        
        // Envia o dígito mais significativo (Volts inteiros) e liga o ponto decimal (bit 15 / 0x80)
        LATB = (LATB & 0x80FF) | ((int)(display7Scodes[digit_high] | 0x80) << 8);
    }
    displayFlag = !displayFlag; // Alterna a flag para a próxima iteração
}

int main(void)
{
    // 1. Configurar portos de saída para os Displays (RB8 a RB15 e RD5, RD6)
    TRISB = TRISB & 0x80FF; // Coloca RB8 a RB15 como saídas
    TRISD = TRISD & 0xFF9F; // Coloca RD5 e RD6 como saídas

    // 2. Configurar o porto RB4 como entrada analógica
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     

    // 3. Configurar o módulo A/D (4 amostras consecutivas)
    AD1CON1bits.SSRC = 7;      
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;     
    AD1CON2bits.SMPI = 3;      // 4 amostras
    AD1CHSbits.CH0SA = 4;      

    AD1CON1bits.ON = 1;        // Ativa conversor A/D

    int i = 0;
    int v = 0;                 // Amplitude da tensão (0 a 33)
    unsigned char bcd_v = 0;   // Valor em BCD para os displays

    while(1)
    {

        if(i == 0) 
        {
            // Iniciar a conversão
            AD1CON1bits.ASAM = 1;  
            while(IFS1bits.AD1IF == 0); // Esperar pelo fim

            // Ler o buffer e calcular a média
            int *p = (int *)(&ADC1BUF0);
            int j, soma = 0;
            for(j = 0; j < 4; j++) 
            {
                soma += p[j*4]; 
            }
            int val_ad = soma / 4;

            // Calcular a tensão 0-33 e converter para BCD
            v = (val_ad * 33 + 511) / 1023;
            bcd_v = toBcd((unsigned char)v); 

            //reset flag AD1IF 
            IFS1bits.AD1IF = 0; 
        }


        send2displays(bcd_v);


        resetCoreTimer();
        while(readCoreTimer() < 200000); // 20 MHz / 100 Hz = 200.000 ticks


        i = (i + 1) % 20; 
    }

    return 0;
}
