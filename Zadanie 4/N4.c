#include <stdio.h>
#include <stdlib.h>

#define N 1000
#define H 0.002

double data (int k){
    double x = -1 + k*H;
    return  1/(1+(25* x*x));
} 

int main(){
    int i;
    double matrix_w[N - 1] = {};
    double vector_z[N - 1] = {};
    double vector_q[N - 1] = {};
    double vector_u[N - 1] = {0.0};
    double matrix_c[N - 2] = {0.0};
    double matrix_wyn[N - 1] = {};
    

    FILE *fpwynik1;

     if((fpwynik1=fopen("wynik1.txt", "w"))==NULL) {
     printf ("cant open file1!\n");
     exit(1);
   }

    for(int i = 0; i < N - 1; i++){
        matrix_w[i] = (6/(H*H))*(data(i) - 2*data(i+1) + data(i+2));
    }

//Zastosowanie dla obliczania Thomasa
 
    matrix_c[0] = 1/3;
    matrix_w[0] = matrix_w[0] / 3;

    for ( int i = 1; i < N - 2; i++){
        if(i < N - 3)

        matrix_c[i] = 1/(4 - matrix_c[i-1]);

       matrix_w[i] = (matrix_w[i] - matrix_w[i-1]) / (4 - matrix_c[i-1]);
    }
    matrix_c[N - 3] = 1/ (3 - matrix_c[N - 4]);
    matrix_w[N - 2] = (matrix_w[N - 2] - matrix_w[N - 3]) / (3 - matrix_c[N-3]);
    vector_z[N - 2] = matrix_w[N - 2];

    for(int i = N-3 ; i >= 0; i--){
        vector_z[i] = matrix_w[i] - matrix_c[i] * vector_z[i+1];
    }

//Zastosowanie dla obliczania Thomasa
    vector_u[0] = 1;
    vector_u[N - 2] = 1;
    matrix_c[0] = 1/3;
    vector_u[0] = vector_u[0] / 3;

    for ( int i = 1; i < N - 2; i++){
        if(i < N - 3)
        matrix_c[i] = 1/(4 - matrix_c[i-1]);

        vector_u[i] = (vector_u[i] - vector_u[i-1]) / (4 - matrix_c[i-1]);
    }

    matrix_c[N - 3] = 1/ (3 - matrix_c[N - 4]);
    vector_u[N - 2] = (vector_u[N - 2] - vector_u[N - 3]) / (3 - matrix_c[N-3]);
    vector_q[N - 2] = vector_u[N - 2];


    for(int i = N-3 ; i >= 0; i--){
        vector_q[i] = vector_u[i] - matrix_c[i] * vector_q[i+1];
    }

    double div;
    double scalar;

    scalar = vector_z[0] + vector_z[N - 2];
    div = 1 + vector_q[0] + vector_q[N - 2];

    for(i = 0; i< N-1; i++){
        vector_q[i] = vector_q[i] * scalar / div;
        matrix_wyn[i] = vector_z[i] - vector_q[i];
    }



    for(int i = 0 ; i < N - 1 ; i++){
        fprintf (fpwynik1," %i %.16lf %.16lf \n",i+1 ,-1 + i*H, matrix_wyn[i] ); 
    }
}