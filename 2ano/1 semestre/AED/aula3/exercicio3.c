#include <stdio.h>

int main(void)
{
    int power[10] = {0, 1, 8, 27, 64, 125, 216, 343, 512, 729}; // Cubos de 0 a 9
    int NDIVS = 0, NMULTS = 0;

    for (int i = 100; i < 1000; i++)
    {
        int cent = i / 100;
        int dez = (i / 10) % 10;
        int uni = i % 10;
        NDIVS += 4;

        if (i == (power[cent] + power[dez] + power[uni]))
        {
            printf("Número encontrado : %d\n", i);
        }
    }

    printf("Total de divisões: %d\n", NDIVS);
    printf("Total de multiplicações: %d\n", NMULTS);

    return 0;
}
