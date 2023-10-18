#include <stdio.h>
#include <stdlib.h>

#define N 1001
#define H 0.001

int main(){
    double d[N] = {0.0};
    double c[N - 1] = {};
    double u[N] = {0.0};
    double x[N];
    double diagonal = 2.000001;
    FILE *fpwynik1;

    if((fpwynik1=fopen("wynik_a.txt", "w"))==NULL) {
        printf ("cant open file1!\n");
        exit(1);
    }
    /*Zapełnianie macierzy wyników*/
    d[0] = 1.0;
    d[N - 1] = 1.0;
    /*--------------------------------*/
    c[0] = 0;
   

    for ( int i = 1; i < N ; i++){
       if(i < N - 1){
       c[i] = -1/(diagonal - (-1*c[i-1]));
       }
       if(i ==1){
       c[i] = -1/(diagonal - (0*c[i-1]));
       }

       d[i] = (d[i] - (-1 * d[i-1])/(diagonal - (-1*c[i-1])));
    }

    u[N - 1] = d[N - 1];

    for(int i = N - 1 ; i >= 0; i--){
        u[i] = d[i] - c[i] * u[i+1];
    }

    for(int i = 0 ; i < N -1 ; i++){
        x[i] = i*H;
        fprintf (fpwynik1," %i %.16lf %.16lf \n",i+1 ,x[i], u[i] );
        printf(" %i %.16lf %.16lf \n",i+1 ,x[i], u[i]);
    }
}