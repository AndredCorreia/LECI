#include <detpic32.h>

int main(void)
{
    // Configurar o porto RB4 como entrada analógica
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;     

    // Configurar o módulo A/D
    AD1CON1bits.SSRC = 7;      
    AD1CON1bits.CLRASAM = 1;   
    AD1CON3bits.SAMC = 16;     
    AD1CON2bits.SMPI = 3;      // 4 conversões consecutivas (SMPI = 3)
    AD1CHSbits.CH0SA = 4;      

    AD1CON1bits.ON = 1;        // Ativa o conversor A/D

    while(1)
    {
        // Iniciar a amostragem/conversão
        AD1CON1bits.ASAM = 1;  

        // Esperar pelo fim das 4 conversões
        while(IFS1bits.AD1IF == 0); 

        // 1. Calcular a média das 4 amostras
        int *p = (int *)(&ADC1BUF0);
        int i, soma = 0;
        
        for(i = 0; i < 4; i++) 
        {
            // p[i*4] avança corretamente no buffer (saltos de 16 bytes)
            soma += p[i*4]; 
        }
        int val_ad = soma / 4; // Média das 4 amostras

        // 2. Determinar a amplitude da tensão (valor de 0 a 33, correspondendo a 0.0V - 3.3V)
        int v = (val_ad * 33 + 511) / 1023;

        // 3. Imprimir o valor calculado
        // Parte inteira da tensão
        printInt(v / 10, 10 | 1 << 16); 
        putChar('.');
        // Parte decimal da tensão
        printInt(v % 10, 10 | 1 << 16); 
        putChar(' ');
        putChar('V');
        
        // Regressar ao início da linha e apagar caracteres extra (espaços em branco)
        printStr("   \r"); 

        // Fazer reset à flag AD1IF
        IFS1bits.AD1IF = 0; 
        
        // Atraso para que o ecrã não atualize demasiado depressa (~10 Hz)
        resetCoreTimer();
        while(readCoreTimer() < 2000000); 
    }

    return 0;
}
