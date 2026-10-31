#include <detpic32.h>

int main(void) {
    // 1. Configurar portos dos displays de 7 segmentos
    TRISB = TRISB & 0x80FF; // RB8 a RB14 como saídas (Segmentos)
    TRISD = TRISD & 0xFF9F; // RD5 e RD6 como saídas (Seleção dos displays)

    // 2. Configurar o Módulo A/D (Usando o canal AN4 - ligado ao pino RB4)
    TRISBbits.TRISB4 = 1;       // Ligar RB4 como entrada
    AD1PCFGbits.PCFG4 = 0;      // Configurar RB4 como entrada analógica (AN4)
    AD1CHSbits.CH0SA = 4;       // <-- CRUCIAL: Selecionar o canal AN4 para conversão
    
    AD1CON1bits.SSRC = 7;       // Conversão automática (Auto-convert)
    AD1CON1bits.CLRASAM = 1;    // Parar amostragem após a flag de conversão disparar
    AD1CON3bits.SAMC = 16;      // Tempo de amostragem (16 TAD)
    AD1CON2bits.SMPI = 1;       // Gerar flag após 2 conversões consecutivas (N-1)
    AD1CON1bits.ON = 1;         // Ativar Módulo ADC

    // Temporizadores não bloqueantes (Core Timer a 20MHz)
    unsigned int timer_10Hz = readCoreTimer();
    unsigned int timer_refresh = readCoreTimer();
    
    unsigned int media_adc = 0;
    unsigned char display_flag = 0; // Para garantir duty-cycle de 50% na multiplexagem

    while(1) {
        // --- LEITURA DO ADC E ENVIO PARA PC (10 Hz) ---
        if (readCoreTimer() - timer_10Hz >= 2000000) { 
            timer_10Hz += 2000000;
            
            // Iniciar a amostragem
            AD1CON1bits.ASAM = 1;       
            
            // Polling: Esperar em ciclo fechado pela flag de fim de conversão
            while(IFS1bits.AD1IF == 0); 
            
            // Ler os buffers e fazer a média das 2 conversões
            media_adc = (ADC1BUF0 + ADC1BUF1) / 2; 
            
            // Limpar a flag obrigatoriamente
            IFS1bits.AD1IF = 0;         

            // Enviar valor para o PC via UART (Hexadecimal formatado a 3 dígitos)
            // A função printInt permite definir a base e o nº de dígitos no 2º argumento
            printInt(media_adc, 16 | (3 << 16)); 
            putChar('\n');
            putChar('\r');
        }

        // --- GESTÃO DOS DISPLAYS (100 Hz) ---
        if (readCoreTimer() - timer_refresh >= 200000) { 
            timer_refresh += 200000;
            
            // Desligar ambos os displays temporariamente para evitar "ghosting"
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 0;

            // Converter a tensão de 1.2V para o valor lido pelo ADC:
            // Regra de 3 simples para 10-bits: (1.2V / 3.3V) * 1023 ≈ 372
            if (media_adc < 372) {
                // Inferior a 1.2V -> Mostrar 'A' (código 0x77) no display menos significativo
                if (display_flag == 0) {
                    LATB = (LATB & 0x80FF) | (0x77 << 8);
                    LATDbits.LATD5 = 1; // Liga LSD
                }
            } else {
                // Superior ou igual a 1.2V -> Mostrar 'B' (código 0x7C) no display mais significativo
                if (display_flag == 1) {
                    LATB = (LATB & 0x80FF) | (0x7C << 8);
                    LATDbits.LATD6 = 1; // Liga MSD
                }
            }
            
            // Alternar a flag. Mesmo que apenas um display seja usado, 
            // isto garante que a luminosidade é idêntica à de códigos multiplexados normais
            display_flag = !display_flag; 
        }
    }
    return 0;
}
