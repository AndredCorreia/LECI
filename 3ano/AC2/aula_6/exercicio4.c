#include <detpic32.h>

int main(void)
{
    // 1. Configurar o porto RB4 como entrada analógica
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     

    // 2. Configurar o módulo A/D
    AD1CON1bits.SSRC = 7;      // Conversão automática
    AD1CON1bits.CLRASAM = 1;   // Para as conversões quando é gerada a interrupção
    AD1CON3bits.SAMC = 16;     // Tempo de amostragem: 16 TAD
    
    // ALTERAÇÃO AQUI: 4 conversões consecutivas (SMPI = 4 - 1 = 3)
    AD1CON2bits.SMPI = 3;      
    
    AD1CHSbits.CH0SA = 4;      // Canal AN4

    AD1CON1bits.ON = 1;        // Ativa o conversor A/D

    while(1)
    {
        // Dá ordem para iniciar a amostragem/conversão
        AD1CON1bits.ASAM = 1;  

        // Espera pelo fim das 4 conversões (AD1IF só vai a 1 após as 4 amostras)
        while(IFS1bits.AD1IF == 0); 

        // Lê e imprime as 16 posições do buffer
        int *p = (int *)(&ADC1BUF0);
        for(; p <= (int *)(&ADC1BUFF); p+=4 ) 
        {
            printInt( *p, 10 | 4 << 16 ); // Imprime em base 10, com 4 dígitos
            putChar(' ');                 // Separa os valores
        }
        
        // Regressa ao início da linha para atualizar os valores de forma fluida
        putChar('\r'); 

        // Faz reset à flag AD1IF
        IFS1bits.AD1IF = 0; 
        
        // Atraso de ~100ms para facilitar a leitura no terminal
        resetCoreTimer();
        while(readCoreTimer() < 2000000); 
    }

    return 0;
}
