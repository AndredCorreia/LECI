#include <detpic32.h>

// Variável global para partilha entre ISR da ADC e ISR do Timer T3
volatile int voltage = 0; 

// Alínea a) - Funções auxiliares e BCD
unsigned char toBcd(unsigned char value) 
{
    return ((value / 10) << 4) + (value % 10);
}

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
        LATB = (LATB & 0x80FF) | ((int)display7Scodes[digit_low] << 8);
    } 
    else 
    {
        LATDbits.LATD5 = 0; // Desativa display Low
        LATDbits.LATD6 = 1; // Ativa display High
        // Envia dígito High com ponto decimal (bit 15 / 0x80)
        LATB = (LATB & 0x80FF) | ((int)(display7Scodes[digit_high] | 0x80) << 8);
    }
    displayFlag = !displayFlag;
}

// Alínea b) - Configurações
void configureAll(void)
{
    // 1. Saídas para Displays (RB8-RB15 e RD5-RD6)
    TRISB = TRISB & 0x80FF; 
    TRISD = TRISD & 0xFF9F; 

    // 2. Entrada Analógica AN4
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     

    // 3. Módulo A/D
    AD1CON1bits.SSRC = 7;      
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;     
    AD1CON2bits.SMPI = 3;      // 4 amostras
    AD1CHSbits.CH0SA = 4;      
    AD1CON1bits.ON = 1;        

    // 4. Timer T1 (5 Hz -> 200ms)
    // PBCLK = 20MHz, Prescaler = 256 -> 20MHz/256 = 78125Hz. PR1 = 78125/5 - 1 = 15624
    T1CONbits.TCKPS = 3; 
    PR1 = 15624;
    TMR1 = 0;
    T1CONbits.ON = 1;

    // 5. Timer T3 (100 Hz -> 10ms)
    // PBCLK = 20MHz, Prescaler = 32 -> 20MHz/32 = 625000Hz. PR3 = 625000/100 - 1 = 6249
    T3CONbits.TCKPS = 5; 
    PR3 = 6249;
    TMR3 = 0;
    T3CONbits.ON = 1;

    // 6. Configuração de Interrupções
    IPC1bits.T1IP = 2;  // Prioridade Timer 1
    IEC0bits.T1IE = 1;  // Enable T1

    IPC3bits.T3IP = 2;  // Prioridade Timer 3
    IEC0bits.T3IE = 1;  // Enable T3

    IPC6bits.AD1IP = 3; // Prioridade ADC (superior aos timers)
    IEC1bits.AD1IE = 1; // Enable ADC
    
    // Configurar o controlador para modo Multi-Vetor (Essencial para evitar a Exception)
    INTCONbits.MVEC = 1; 
}

int main(void)
{
    configureAll();

    // Reset de todas as flags antes de começar
    IFS1bits.AD1IF = 0;
    IFS0bits.T1IF = 0;
    IFS0bits.T3IF = 0;

    EnableInterrupts(); 

    while(1)
    {
        // O trabalho é todo feito nas ISRs
    }
    return 0;
}

// Alínea c) - ISR Timer T1 (Inicia conversão)
void _int_(4) isr_T1(void)
{
    AD1CON1bits.ASAM = 1; // Ordem de início de conversão
    IFS0bits.T1IF = 0;    // Reset T1IF flag
}

// Alínea e) - ISR ADC (Cálculo da média e tensão)
void _int_(27) isr_adc(void)
{
    int *p = (int *)(&ADC1BUF0);
    int j, soma = 0;
    for(j = 0; j < 4; j++) 
    {
        soma += p[j*4]; 
    }
    int val_ad = soma / 4;

    // Converte para escala 0-33 (para mostrar 0.0 a 3.3V)
    voltage = (val_ad * 33 + 511) / 1023;

    IFS1bits.AD1IF = 0; // Reset AD1IF flag
}

// Alínea d) - ISR Timer T3 (Refresh dos displays)
void _int_(12) isr_T3(void)
{
    // Envia o valor atual da global "voltage" em BCD para os displays
    send2displays(toBcd((unsigned char)voltage));
    IFS0bits.T3IF = 0; // Reset T3IF flag
}
