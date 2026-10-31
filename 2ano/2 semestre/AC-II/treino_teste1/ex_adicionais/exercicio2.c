#include <detpic32.h>

// Função auxiliar para enviar o valor para os displays
void send2displays(unsigned char value, unsigned char show_display, unsigned char display_select) {
    static const unsigned char display_codes[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
        0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
    };
    
    // 1. Desligar ambos os displays temporariamente
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;

    // 2. Se for para mostrar o display, atualiza os segmentos e liga o respetivo
    if (show_display) {
        unsigned char digit = display_codes[value];
        // Enviar para os portos RB8 a RB14
        LATB = (LATB & 0x80FF) | ((unsigned int)digit << 8);

        // Ligar o display correspondente (0 = LSD, 1 = MSD)
        if (display_select == 1) {
            LATDbits.LATD6 = 1; 
        } else {
            LATDbits.LATD5 = 1; 
        }
    }
}

int main(void) {
    // Configurações das portas de Entrada/Saída
    TRISE = TRISE & 0xFF80; // RE6 a RE0 como saídas (LEDs para o contador binário)
    TRISB = TRISB | 0x0003; // RB1 e RB0 como entradas (Dip-switches DS2 e DS1)
    TRISB = TRISB & 0x80FF; // RB8 a RB14 como saídas (Segmentos dos displays)
    TRISD = TRISD & 0xFF9F; // RD5 e RD6 como saídas (Seleção dos displays)

    // Variáveis de controlo de tempo (Core Timer a 20 MHz)
    unsigned int timer_100Hz = readCoreTimer();
    unsigned int timer_5Hz = readCoreTimer();
    
    // Variáveis de estado
    unsigned char counter = 0;
    unsigned char pc_key_msd = 0;
    unsigned char pc_key_lsd = 0;
    unsigned char display_flag = 0; // Alterna entre 0 (LSD) e 1 (MSD)

    while(1) {
        // --- LEITURA DAS ENTRADAS ---
        unsigned char switches = PORTB & 0x0003;
        char key = inkey(); // Ler tecla do PC (retorna 0 se não houver tecla)
        
        if (key >= '1' && key <= '9') {
            if (switches == 1) {
                pc_key_msd = key - '0';
            } else if (switches == 2) {
                pc_key_lsd = key - '0';
            }
        }

        // --- GESTÃO DO CONTADOR (5 Hz) ---
        if (readCoreTimer() - timer_5Hz >= 4000000) { 
            timer_5Hz += 4000000;
            
            counter++;
            if (counter >= 60) {
                counter = 0;
            }
            // Mostrar o contador em binário nos LEDs RE6 a RE0
            LATE = (LATE & 0xFF80) | counter; 
        }

        // --- MULTIPLEXAGEM DOS DISPLAYS (100 Hz) ---
        if (readCoreTimer() - timer_100Hz >= 200000) { 
            timer_100Hz += 200000;
            
            unsigned char val_to_show = 0;
            unsigned char show = 1; // 1 = Ligar, 0 = Desligar

            // Avaliar o estado dos switches (0 a 3)
            if (switches == 0) {
                show = 0;
            } else if (switches == 1) {
                if (display_flag == 1) val_to_show = pc_key_msd;
                else show = 0;
            } else if (switches == 2) {
                if (display_flag == 0) val_to_show = pc_key_lsd;
                else show = 0;
            } else if (switches == 3) {
                if (display_flag == 1) val_to_show = counter >> 4; // Extrair nibble alto (Hex MSD)
                else val_to_show = counter & 0x0F;                 // Extrair nibble baixo (Hex LSD)
            }

            // Atualizar hardware e alternar flag
            send2displays(val_to_show, show, display_flag);
            display_flag = !display_flag; 
        }
    }
    return 0;
}
