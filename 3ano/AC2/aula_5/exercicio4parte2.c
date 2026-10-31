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
    unsigned int freq_divider;
    unsigned int timer_led = 0; // Temporizador para o RC14

    TRISB = (TRISB & 0x80FF) | 0x0001;
    TRISD = TRISD & 0xFF9F;
    TRISE = TRISE & 0xFF00;
    TRISCbits.TRISC14 = 0; // Configura RC14 como saída
    LATCbits.LATC14 = 0;   // Garante que o LED começa desligado

    while(1) {
        i = 0;
        if (PORTBbits.RB0 == 1) freq_divider = 20; // 5 Hz
        else freq_divider = 50;                    // 2 Hz

        do {
            send2displays(toBcd(counter));
            LATE = (LATE & 0xFF00) | toBcd(counter);
            
            // Gestão do LED dos 5 segundos de forma não-bloqueante
            if (timer_led > 0) {
                LATCbits.LATC14 = 1;
                timer_led--; // Decrementa 1 a cada 10ms
            } else {
                LATCbits.LATC14 = 0;
            }
            
            delay(10);
        } while (++i < freq_divider);

        // Lógica Up/Down e ativação do temporizador do LED
        if (PORTBbits.RB0 == 1) {
            counter++;
            if (counter >= 60) {
                counter = 0;
                timer_led = 500; // 5s = 500 ciclos de 10ms
            }
        } else {
            if (counter == 0) {
                counter = 59;
                timer_led = 500; // 5s = 500 ciclos de 10ms
            } else {
                counter--;
            }
        }
    }
    return 0;
}
