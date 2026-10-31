#include <detpic32.h>


volatile int voltage = 0; 
// Novas variáveis globais pedidas no guião para armazenar o mínimo e o máximo [cite: 138]
volatile int voltMin = 33; 
volatile int voltMax = 0;  

// --------------------------------------------------------
// FUNÇÕES AUXILIARES (Displays e UART)
// --------------------------------------------------------
unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}

void send2displays(unsigned char value) {
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0; 

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;

    if (displayFlag == 0) {
        LATDbits.LATD5 = 1; // Ativa display Low
        LATDbits.LATD6 = 0; // Desativa display High
        LATB = (LATB & 0x80FF) | ((int)display7Scodes[digit_low] << 8);
    } else {
        LATDbits.LATD5 = 0; // Desativa display Low
        LATDbits.LATD6 = 1; // Ativa display High
        LATB = (LATB & 0x80FF) | ((int)(display7Scodes[digit_high] | 0x80) << 8);
    }
    displayFlag = !displayFlag;
}

// Nova função sugerida no guião para converter e enviar para a UART por polling [cite: 146, 147, 148]
void sendVoltage(char* prefix, int value) {
    printStr(prefix); 
    
    char digit_high = (value / 10) + '0';
    char digit_low = (value % 10) + '0';
    
    putChar(digit_high);
    putChar('.');
    putChar(digit_low);
    putChar('V');
    putChar('\n');
}

// --------------------------------------------------------
// CONFIGURAÇÕES GERAIS
// --------------------------------------------------------
void configureAll(void) {
    // 1 a 6. Configurações originais da aula 9 (Displays, ADC, T1, T3)
    TRISB = TRISB & 0x80FF; 
    TRISD = TRISD & 0xFF9F; 
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     
    AD1CON1bits.SSRC = 7;      
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;     
    AD1CON2bits.SMPI = 3;      // 4 amostras
    AD1CHSbits.CH0SA = 4;      
    AD1CON1bits.ON = 1;        

    T1CONbits.TCKPS = 3; 
    PR1 = 15624;
    TMR1 = 0;
    T1CONbits.ON = 1;

    T3CONbits.TCKPS = 5; 
    PR3 = 6249;
    TMR3 = 0;
    T3CONbits.ON = 1;

    IPC1bits.T1IP = 2;  
    IEC0bits.T1IE = 1;  
    IPC3bits.T3IP = 2;  
    IEC0bits.T3IE = 1;  
    IPC6bits.AD1IP = 3; 
    IEC1bits.AD1IE = 1; 
    
    // 7. Novas Configurações da UART2 
    U2BRG = ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1; 
    IEC1bits.U2TXIE = 0; 
    IPC8bits.U2IP = 2;   
    IFS1bits.U2RXIF = 0; 
    U2STAbits.URXISEL = 0;

    INTCONbits.MVEC = 1; 
}

// --------------------------------------------------------
// PROGRAMA PRINCIPAL
// --------------------------------------------------------
int main(void) {
    configureAll();

    IFS1bits.AD1IF = 0;
    IFS0bits.T1IF = 0;
    IFS0bits.T3IF = 0;

    EnableInterrupts(); 

    while(1) {
        IdleMode(); // Adicionado para poupar energia enquanto as interrupções não chegam
    }
    return 0;
}

// --------------------------------------------------------
// ROTINAS DE SERVIÇO À INTERRUPÇÃO (ISRs)
// --------------------------------------------------------

// ISR Timer T1 (Inicia conversão ADC)
void _int_(4) isr_T1(void) {
    AD1CON1bits.ASAM = 1; 
    IFS0bits.T1IF = 0;    
}

// ISR Timer T3 (Refresh dos displays de 7 segmentos)
void _int_(12) isr_T3(void) {
    send2displays(toBcd((unsigned char)voltage));
    IFS0bits.T3IF = 0; 
}

// ISR ADC (Cálculo da tensão e registo de Mínimos/Máximos)
void _int_(27) isr_adc(void) {
    int *p = (int *)(&ADC1BUF0);
    int j, soma = 0;
    for(j = 0; j < 4; j++) {
        soma += p[j*4]; 
    }
    int val_ad = soma / 4;

    voltage = (val_ad * 33 + 511) / 1023;

    // Adicionado: Atualização das variáveis voltMin e voltMax [cite: 139]
    if (voltage > voltMax) voltMax = voltage;
    if (voltage < voltMin) voltMin = voltage;

    IFS1bits.AD1IF = 0; 
}

// Nova ISR da UART2 (Controla a ADC pelo teclado do PC) [cite: 145, 149]
void _int_(32) isr_uart2(void) {
    if (IFS1bits.U2RXIF == 1) {
        char c = U2RXREG; // Lê o caracter recebido
        
        if (c == 'M') {
            sendVoltage("VMax=", voltMax);
        } 
        else if (c == 'm') {
            sendVoltage("VMin=", voltMin);
        } 
        // Comandos adicionados do Exercício 2
        else if (c == 'p') {
            // Desativa a interrupção do Timer 1 (que controla o início de conversão) 
            IEC0bits.T1IE = 0; 
        } 
        else if (c == 'R' || c == 'r') {
            // Reativa a interrupção do Timer 1 
            IEC0bits.T1IE = 1; 
        } 
        else if (c == 's') {
            // Envia o status [cite: 161]
            if (IEC0bits.T1IE == 1) printStr("ADC ativa\n"); 
            else printStr("ADC inativa\n"); 
        }

        IFS1bits.U2RXIF = 0;
    }
}
