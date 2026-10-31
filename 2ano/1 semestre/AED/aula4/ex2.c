#include <stdio.h>

int f2(double* p, size_t size, unsigned int* p_ndivs) {
    double r = p[1] / p[0];
    *p_ndivs = 1;
    for (unsigned int i = 1; i < size - 1; i++) {
        (*p_ndivs)++;
        if (p[i+1] / p[i] != r)
            return 0;
    }
    return 1;
}

int main(void) {
    double array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double array2[] = {1, 2, 4, 4, 5, 6, 7, 8, 9, 10};
    double array3[] = {1, 2, 4, 8, 5, 6, 7, 8, 9, 10};
    double array4[] = {1, 2, 4, 8, 16, 6, 7, 8, 9, 10};
    double array5[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512}; // Nome único para este array

    double* arrays[] = {array1, array2, array3, array4, array5}; // Conjunto de arrays

    for (int i = 0; i < 5; i++) {
        unsigned int ndivs = 0;  // Inicializa contador de divisões
        int result = f2(arrays[i], 10, &ndivs);  // Chama a função f2
        printf("O array %d %s uma progressão geométrica.\n", i+1, result ? "é" : "não é");
        printf("Foram realizadas %d divisões.\n", ndivs);
    }

    return 0;
}
