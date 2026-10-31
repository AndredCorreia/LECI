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

unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}

int main(void) {
    unsigned int i;
    unsigned char counter = 0;

    // Configuração dos portos
    TRISB = TRISB & 0x80FF; // RB8-RB14 saídas (displays)
    TRISD = TRISD & 0xFF9F; // RD5-RD6 saídas (controlo displays)
    TRISE = TRISE & 0xFF00; // RE0-RE7 saídas (LEDs)

    while(1) {
        i = 0;
        // Refrescamento a 100Hz (10ms) e contagem a 2Hz (500ms = 50 * 10ms)
        do {
            send2displays(toBcd(counter));
            LATE = (LATE & 0xFF00) | toBcd(counter); // Mostra BCD nos LEDs
            delay(10);
        } while (++i < 50);

        // Contador crescente mod 60
        counter++;
        if (counter >= 60) {
            counter = 0;
        }
    }
    return 0;
}



