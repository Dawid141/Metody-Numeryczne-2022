#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1000
#define H 0.002

double data (int k){
    double x = -1 + k*H;
    return  (1/(1+(25* x*x))); 
} 

int main(){
    double d[N - 1];
    double c[N - 2];
    double u[N - 1];
    FILE *fpwynik1;

     if((fpwynik1=fopen("wynik1.txt", "w"))==NULL) {
     printf ("cant open file1!\n");
     exit(1);
   }

    for(int i = 0; i < N - 1; i++){
        d[i] = (6/(H*H))*(data(i) - 2*data(i+1) + data(i+2));
    }

    c[0] = 1/4;
    d[0] = d[0] / 4;
    for ( int i = 1; i < N - 1; i++){
        if(i < N - 2){

        c[i] = 1/(4 - c[i-1]);

        }
        d[i] = (d[i] - d[i-1]) / (4 - c[i-1]);
    }

    u[N - 2] = d[N - 2];

    for(int i = N-3 ; i >= 0; i--){
        u[i] = d[i] - c[i] * u[i+1];
    }

    for(int i = 0 ; i < N - 1 ; i++){
        
        fprintf (fpwynik1," %i %.16lf %.16lf \n",i+1 ,-1 + i*H, u[i] ); 
    }
}