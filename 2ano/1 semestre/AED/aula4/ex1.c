#include <stdio.h>

int NCOMPS;  

int funcao1(int* p, size_t size, int* p_COMPS) {
    int n = 0;
    for (int i = 1; i < size - 1; i++) {
        if (p[i] == (p[i-1] + p[i+1])) {
            n++;
        }
        (*p_COMPS)++;  
    }
    return n;
}

int main(void) {
    int comp = 0;
    int* p_comp = &comp;
    int array0[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array1[] = {1, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    int array2[] = {1, 2, 1, 3, 2, 6, 7, 8, 9, 10};
    int array3[] = {0, 2, 2, 0, 3, 3, 0, 4, 4, 0};
    int array4[] = {0, 0, 0, 0, 0, 0,0,0,0, 0};
    int* arrays[] = {array0, array1, array2, array3, array4};

    for (int i = 0; i < 5; i++) {
        comp = 0;  
        int n_sucess = funcao1(arrays[i], 10, p_comp);  
        printf("O número de elementos no array que satisfazem a condição é %d\n", n_sucess);
        printf("Foram realizadas %d comparações.\n", comp);
    }
}
