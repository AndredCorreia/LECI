#include <detpic32.h>

int main(void)
{
    volatile int aux; 
    int time_ticks;
    int tempo_ns;
    int start_delay;


    TRISBbits.TRISB4 = 1;       // RB4 configurado como entrada digital
    AD1PCFGbits.PCFG4 = 0;      // RB4 configurado como entrada analógica (AN4)
    AD1CON1bits.SSRC = 7;       // Conversão automática após fim da amostragem
    AD1CON1bits.CLRASAM = 1;    // Parar conversões após a 1ª terminar
    AD1CON3bits.SAMC = 16;      // Tempo de amostragem (16 TAD)
    AD1CON2bits.SMPI = 0;       // Interromper após 1 conversão
    AD1CHSbits.CH0SA = 4;       // Canal AN4 selecionado
    AD1CON1bits.ON = 1;         // Ativar o módulo A/D

    while(1)
    {
        // Iniciar conversão
        AD1CON1bits.SAMP = 1; 


        resetCoreTimer();

	//esperar fim de conversao
        while(IFS1bits.AD1IF == 0);


        time_ticks = readCoreTimer();

        // Ler resultado da conversão
        aux = ADC1BUF0;

        // reset flag de interrupção
        IFS1bits.AD1IF = 0;


        tempo_ns = time_ticks * 50; 

        printStr("Tempo de conversao: ");
        printInt(time_ticks, 10);
        printStr(" ticks (");
        printInt(tempo_ns, 10);
        printStr(" ns)\r"); 
        
        
        start_delay = readCoreTimer();
        while((readCoreTimer() - start_delay) < 10000000); 
    }
    return 0;
}
