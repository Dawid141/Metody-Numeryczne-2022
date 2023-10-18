#include <stdio.h>
#include <math.h>

#define N 1001

void conjugateGradients(double* vectorN) {
    double norm = 1.0;
    int il=0;
    double h2 = 2.000001;
    double r[N], rNew[N], p[N], Ap[N], alpha, beta;
    double divident = 0.0;
    double divisor = 0.0;

    r[0] = 1.0 - vectorN[0];
    r[N - 1] = 1.0 - vectorN[N - 1];

    for(int i = 1; i < N - 1; i++)
        r[i] = vectorN[i - 1] + vectorN[i + 1] - h2 * vectorN[i];

    for(int i = 0; i < N; i++)
        p[i] = r[i];

    for(int j = 0; j < 10000000; j++) {
        Ap[0] = p[0];
        Ap[N - 1] = p[N - 1];

        for(int i = 1; i < N - 1; i++)
            Ap[i] = h2 * p[i] - p[i - 1] - p[i + 1];

        for(int i = 0; i < N; i++){
            divident += r[i] * r[i];
            divisor += p[i] * Ap[i];
        }

        alpha = divident / divisor;

        for(int i = 0; i < N; i++)
            rNew[i] = r[i] - alpha * Ap[i];

        for(int i = 0; i < N; i++){
            divident += rNew[i] * rNew[i];
            divisor += r[i] * r[i];
        }

        beta = divident / divisor;

        for(int i = 0; i < N; i++)
            vectorN[i] = vectorN[i] + alpha * p[i];

        for(int i = 0; i < N; i++) {
            p[i] = rNew[i] + beta * p[i];
            r[i] = rNew[i];
        }
        il++;
        if(vectorN[500]== 0.8868188925)
        {printf("%i\n",il);
            break;}
    }
}


int main() {
    double x[N] = {0.0};
    FILE *data;
     data  = fopen("wynikGradient.txt","w"); 
    if(!data){
        perror("Error opening file");
        exit(1);
    }

    conjugateGradients(x);
    for(int i = 0; i < N; i++){
        
        fprintf(data, "%i\t %.10lf \n",i,x[i]);
        }
}