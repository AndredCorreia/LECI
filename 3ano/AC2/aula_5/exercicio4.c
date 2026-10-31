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
    TRISB = TRISB & 0x80FF; // Configurar RB8-RB14 como saídas 
    TRISD = TRISD & 0xFF9F; // Configurar RD5-RD6 como saídas 

    while(1) {
        send2displays(0x15); // 
        delay(10);          // Esperar 0.2s 
    }
    return 0;
}


