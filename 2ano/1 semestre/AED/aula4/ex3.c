#include <stdio.h>

// Função que conta o número de ternos (i, j, k) e o número de comparações
int f3(int* p, size_t size, unsigned int* ncomps) {
    *ncomps = 0;
    int nternos = 0;
    
    // Três loops para verificar todos os ternos (i, j, k) onde i < j < k
    for (unsigned int i = 0; i < size - 2; i++) {
        for (unsigned int j = i + 1; j < size - 1; j++) {
            for (unsigned int k = j + 1; k < size; k++) {
                (*ncomps)++;
                if (p[k] == p[i] + p[j]) {
                    nternos++;
                }
            }
        }
    }
    return nternos;
}

int main(void) {
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int array4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    int array5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};

    int* arrays[] = {array1, array2, array3, array4, array5};
    int sizes[] = {5, 10, 20, 30, 40}; 
    unsigned int ncomps = 0;  

    for (int i = 0; i < 5; i++) {
        int nternos = f3(arrays[i], sizes[i], &ncomps);  
        printf("Sequência de %d elementos:\n", sizes[i]);
        printf("Número de ternos que satisfazem a condição: %d\n", nternos);
        printf("Número de comparações realizadas: %u\n\n", ncomps);
    }

    return 0;
}
