#include <detpic32.h>

int main(void)
{
    // a) Configurar o porto RB4 como entrada analógica
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     

    // Configurar o módulo A/D
    AD1CON1bits.SSRC = 7;  
    
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;    
    AD1CON2bits.SMPI = 0;      
    AD1CHSbits.CH0SA = 4;      
    AD1CON1bits.ON = 1;        // Ativa A/D

    while(1)
    {

        AD1CON1bits.ASAM = 1;  // Start conversion


        while(IFS1bits.AD1IF == 0); //wait while conversion not done


        // formata para Hexadecimal (16) com 3 dígitos (3 << 16)
        printInt(ADC1BUF0, 16 | 3 << 16); 
        

        putChar('\r' ); 

        // reset flag AD1IF
        IFS1bits.AD1IF = 0; 
        
        
    }

    return 0;
}
