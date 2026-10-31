#include <detpic32.h> 

int main(void) {
    // 1) Configurar os portos RE6-RE3 como saídas
    TRISEbits.TRISE3= 0;
    TRISEbits.TRISE4= 0;
    TRISEbits.TRISE5= 0;
    TRISEbits.TRISE6= 0;

    // 2) Inicializar a variável do contador
    int counter = 0;
    int step = 1;

    while(1) {
        // 3) Atualizar os portos de saída (RE6-RE3)
        // Limpa os bits atuais e faz o shift do contador para a posição correta
        LATE = (LATE & 0xFF87) | (counter << 3);

        // 4) Esperar 1/4.6 s (aproximadamente 217ms)
        // Se SYSCLK = 40MHz, CoreTimer = 20MHz -> 20M / 4.6 = 4347826
        resetCoreTimer();
        while(readCoreTimer() < 7407407);

        // 5) Incrementar a variável do contador, módulo 10
        counter = (counter + step) % 10;

        // 6) O loop while(1) garante a repetição automática
    }

    return 0;
}
