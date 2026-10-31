#include <stdio.h>

int i,j, NADDS;

long long del_(int m, int n){
    long long data[m+1][n+1];
    for (int i=0; i<=m; i++){
        for (int j=0; j<=n;j++){
            if ((i==0)||(j==0)){
                data[i][j]=1;
                NADDS+=2;
                data[i][j]= data[i-1][j]+ data[i-1][j-1]+data[i][j-1];

            }
        }
    }
    return data[i][j];
}