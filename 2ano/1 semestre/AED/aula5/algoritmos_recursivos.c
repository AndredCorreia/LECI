#include <stdio.h>
#include <assert.h>


int N1,N2,N3;
int funcao1 (int n){
    assert(n>=1);
    if (n==1){
        return 1;

    }
    else {
        N1++;
        return funcao1(n/2)+n;
    }
}

int funcao2 (int n){
    assert(n>=1);
    if (n==1){
        return 1;

    }
    else {
        N2+=2;
        return funcao2(n/2)+ funcao2((n+1)/2)+n;
        



    }
}


int funcao3 (int n){
    assert(n>=1);
    if (n==1){
        return 1;
    }
    else if(n%2!=0){
        N3+=2;
        return funcao3(n/2)+ funcao3((n+1)/2)+n;

    }   
    else{
        N3++;
        return 2*funcao3(n/2)+n;

    }
}

int main(void){
    for (int i=1;i<128;i++){
        N1=0;N2=0;N3=0;
        int aux1= funcao1(i);
        int aux2= funcao2(i);
        int aux3= funcao3(i);

        printf("N=%2d F1=%4d N1=%4d | F2=%4d N2=%4d | F3=%4d N3=%4d\n",i,aux1,N1,aux2,N2,aux3,N3);
    }
}