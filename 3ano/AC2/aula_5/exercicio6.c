#include <detpic32.h>

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

void delay(unsigned int ms) {
    // Para cada milissegundo pedido
    for (; ms > 0; ms--) {
        resetCoreTimer(); // Faz reset ao temporizador do processador
        // Espera até que o temporizador atinja 20000 (1 ms a 20 MHz)
        while (readCoreTimer() < 20000); 
    }
}

int main(void) {
    unsigned int i = 0;
    unsigned char counter = 0;

    TRISB = TRISB & 0x80FF; // Outputs para os segmentos
    TRISD = TRISD & 0xFF9F; // Outputs para controlo dos displays

    while(1) {
        i = 0;
        do {
            send2displays(counter); // 
            delay(10);              // Espera 10 ms (frequência de refrescamento a 100Hz) 
        } while (++i < 20);         // Ciclo repete 20 vezes para totalizar 200ms (5Hz)
        counter = (counter + 1) % 256; // Incrementa o contador módulo 256 
    }
    return 0;
}


