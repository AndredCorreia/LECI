#include <stdio.h>



/*int sum (int n,int *a){
    int i,s;
    s=0;

    for (i=0;i<n;i++){
        s+=a[i];
    }
    return s;


    
}

int x=23;
int y=10;
void swap(int *x, int *y){
    int temp=*x;
    *x=*y;
    *y=temp;
    printf("%d %d\n",*x ,*y);
}

int main(void){

    puts("Hello World!");
    int a[10];
    for (int i=0; i<10; i++){
        a[i]=i;

    }
    for (int i =0; i<10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    int *p= &(a[4]);
    for (int i= -4; i<6;i++){
        printf("%d ", p[i]);

    }
    printf("\n");
    printf("Endereço %p",(void *)p);

    printf("\n");
    p[5]= -9;
    for (int i=0;i<10;i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    
    printf("%d\n",sum(10,a));

    swap(&x,&y);
    return 0;
}
*/

void SelectionSort(int *a, unsigned int n) {
    for (unsigned int i = 0; i < n - 1; i++) {
        unsigned int minIndex = i;
        for (unsigned int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = temp;
        }
    }
}
int main(void) {
    // Vetor de teste
    int array[] = {64, 34, 25, 12, 22, 11, 90};
    unsigned int size = sizeof(array) / sizeof(array[0]);

    // Imprime o vetor original
    printf("Vetor original:\n");
    for (unsigned int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Chama a função SelectionSort
    SelectionSort(array, size);

    // Imprime o vetor ordenado
    printf("Vetor ordenado:\n");
    for (unsigned int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}