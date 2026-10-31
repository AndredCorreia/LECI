#include <detpic32.h>

int main(void)
{
    // 1. Configurar o porto RB4 como entrada analógica (AN4)
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     

    // 2. Configurar o módulo A/D
    AD1CON1bits.SSRC = 7;      
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;     
    
    // ALTERAÇÃO: SMPI = 15 para fazer 16 conversões consecutivas 
    // e preencher os 16 buffers (BUF0 até BUFF)
    AD1CON2bits.SMPI = 0;     
    
    AD1CHSbits.CH0SA = 4;      

    // Ativa o conversor A/D
    AD1CON1bits.ON = 1;        

    while(1)
    {
        // Dá ordem para iniciar a amostragem/conversão
        AD1CON1bits.ASAM = 1;  

        // Espera pelo fim das 16 conversões
        while(IFS1bits.AD1IF == 0); 

        // Lê e imprime as 16 posições do buffer
        int *p = (int *)(&ADC1BUF0);
        for(; p <= (int *)(&ADC1BUFF); p+=4 ) 
        {
            // Uso de parêntesis na formatação por segurança
            printInt( *p, 10 | (4 << 16) ); 
            putChar(' ');                   // Separa os valores com 1 espaço
        }
        
        // Regressa ao início da linha para reescrever
        putChar('\r'); 

        // Faz reset à flag AD1IF
        IFS1bits.AD1IF = 0; 
        
        // Atraso de cerca de 100ms
        resetCoreTimer();
        while(readCoreTimer() < 2000000); 
    }

    return 0;
}
