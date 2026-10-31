#include <detpic32.h>    // <--- A linha mágica que resolve os erros!

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < 20000 * ms);
}

int main(void) {
    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    while(1) {
        // Imprime o "Carriage Return" para escrever sempre na mesma linha
        putChar('\r'); 
        
        // Imprime os 3 contadores separados por um espaço
        printInt(cnt1, 0x0005000A);
        putChar(' ');
        printInt(cnt5, 0x0005000A);
        putChar(' ');
        printInt(cnt10, 0x0005000A);

        // Espera 100 milissegundos (Base de tempo de 10 Hz)
        delay(100);

        // Atualiza os contadores
        cnt10++;
        
        if (cnt10 % 2 == 0) {   // A cada 200ms
            cnt5++;
        }
        if (cnt10 % 10 == 0) {  // A cada 1000ms
            cnt1++;
        }
    }
    return 0;
}
