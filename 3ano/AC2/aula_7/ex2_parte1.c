#include <detpic32.h>

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

volatile unsigned char voltage = 0;

void send2displays(unsigned char value) {
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
                                          0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;
    
    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;
    
    if (displayFlag == 0) {
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | ((unsigned int)display7Scodes[digit_low] << 8);
    } else {
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | ((unsigned int)display7Scodes[digit_high] << 8);
    }
    displayFlag = !displayFlag;
}

void _int_(27) isr_adc(void) 
{
    int i, average;
    int sum = 0;
    int *p = (int *)(&ADC1BUF0); 
    
    for(i = 0; i < 8; i++) {
        sum += p[i * 4]; 
    }
    average = sum / 8;
    
    int v = (average * 33 + 511) / 1023; 
    
    voltage = ((v / 10) << 4) | (v % 10);
    
    IFS1bits.AD1IF = 0; 
}

int main(void)
{
    unsigned int cnt = 0;
    
    TRISB = TRISB & 0x80FF; 
    TRISD = TRISD & 0xFF9F;
    
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;
    
    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;
    
    EnableInterrupts();
    
    while(1)
    {
        if(cnt == 0)
        {
            AD1CON1bits.ASAM = 1; 
        }
        
        send2displays(voltage);
        
        cnt = (cnt + 1) % 20; 
        
        delay(10); 
    }
    return 0;
}
