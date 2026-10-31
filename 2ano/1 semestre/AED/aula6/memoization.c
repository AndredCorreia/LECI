#include <stdio.h>
#define MAX 50


long long memdata[MAX+1][MAX+1]={{0}};
long long del_memo(int m, int n){
    if memdata[m][n]!=0{
        return memdata[m][n];

    }
    long long r;
    if ((m==0)||(n==0)){
        r=0;

    }else{
        NADDS+=2;
        r= delmemo(m-1,n) + delmemo(m-1,n-1)+ delmemo(m,n-1);
    }
    memdata[m][n]=r;
    return r;
}