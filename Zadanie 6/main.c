#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define N 101

double Diagonal = 2.000001;
double epsilon = 1e-10;
bool close = false;

void Relaxation(double* vectorN, int* il, double gamma){ 
    *il = 0;
    bool close = false;
    int i;
    double diff;
    double relaxation[N];
    double Ax[N];

    while(!close) {
        for(i = 0; i < N; i++)
            relaxation[i] = vectorN[i];

        Ax[0] = vectorN[0];
        Ax[N - 1] = vectorN[N - 1];
        for(i = 1; i < N - 1; i++)
            Ax[i] = Diagonal * vectorN[i] - vectorN[i - 1] - vectorN[i + 1];

        for(i = 0; i < N; i++)
            if(i == 0 || i == N - 1){
                relaxation[i] += gamma * (1.0 - Ax[i]);
            }
            else{
                 relaxation[i] -= gamma * Ax[i];
            }

        diff = 0.0;
        for(i = 0; i < N; i++){
            diff = fmax(diff, fabs(relaxation[i] - vectorN[i]));
        }
        
        if(diff < epsilon) close = true;
        
        for (i = 0; i < N; i++) {
            vectorN[i] = relaxation[i];
        }
        (*il)++;
    }
}

void Jacobi (double* vectorN, int* il){
    *il = 0;
    bool close = false;
    double diff;
    while(!close) {
        double jacobi[N] = {0.0};
        jacobi[0] = 1.0;
        jacobi[N - 1] = 1.0;

        for (int i = 1; i < N - 1; i++) {
            jacobi[i] = (vectorN[i - 1] + vectorN[i + 1]) / Diagonal;
        }
        diff = 0.0;
        for(int i = 0; i < N; i++){
            diff = fmax(diff, fabs(jacobi[i] - vectorN[i]));
        }

        if(diff < epsilon) close = true;

        for (int i = 0; i < N; i++) {
            vectorN[i] = jacobi[i];
        }
        (*il)++;
    }

}

void GausSeidle(double* vectorN, int* il){
    *il = 0;
    bool close = false;
    double diff;
    while(!close){
        double gausSeidle[N] = {0.0};
        gausSeidle[0] = 1;
        gausSeidle[N - 1] = 1;

        for(int i=1; i < N - 1; i++){
            gausSeidle[i] = vectorN[i+1];
        }

        for(int i = 1; i < N; i++){
            gausSeidle[i] = (gausSeidle[i] + gausSeidle[i-1]) / Diagonal;
        }

        diff = 0.0;
        for(int i = 0; i < N; i++){
            diff = fmax(diff, fabs(gausSeidle[i] - vectorN[i]));
        }

        if(diff < epsilon) close = true;

        for (int i = 0; i < N; i++) {
            vectorN[i] = gausSeidle[i];
        }
        (*il)++;
    }
}

void SuccesiveOverRelaxaton (double* vectorN, int* iterations, double omega) {
    double sor[N];
    *iterations = 0;
    bool stop = false;
    double diff;

    while(!stop) {
        for(int i = 0; i < N; i++)
            sor[i] = vectorN[i] * (1.0 - omega);

        sor[0] += (omega / Diagonal);
        sor[N - 1] += (omega / Diagonal);
        for(int i = 1; i < N - 1; i++) {
            sor[i] += (omega / Diagonal)* (sor[i - 1] + vectorN[i + 1]);
        }

        diff = 0.0;
        for(int i = 0; i < N; i++){
            diff = fmax(diff, fabs(sor[i] - vectorN[i]));
        }

        if(diff < epsilon) stop = true;

        for (int i = 0; i < N; i++) {
            vectorN[i] = sor[i];
        }

        (*iterations)++;
    }
}

void SetAsZero (double vector[N]){
    for(int i = 0; i < N; i++){
        vector[i] = 0.0;
    }
}

int main(){
    double vecZero[N];
    SetAsZero(vecZero);
    int iterations = 0;
    clock_t start;
    clock_t end;
    FILE *data1, *data2, *data3, *data4;
    data1 = fopen("wynikRelaksacyjna.txt","w");
    data2 = fopen("wynikJacobi.txt","w");
    data3 = fopen("wynikGauss.txt","w");  
    data4 = fopen("wynikSOR.txt","w"); 
    if(!data1){
        perror("Error opening file");
        exit(1);
    }
    if(!data2){
        perror("Error opening file");
        exit(1);
    }
    if(!data3){
        perror("Error opening file");
        exit(1);
    }
    if(!data4){
        perror("Error opening file");
        exit(1);
    }

    start = clock();
    Relaxation(vecZero, &iterations, 0.4999);
    end = clock();
    printf("For relaxation method, %d iterations were performed, execution time: %.3f  \n", iterations, (double)(end - start)/CLOCKS_PER_SEC);

    for(int i = 0; i < N; i++)
        fprintf(data1, "%i\t %.10lf \n", i, vecZero[i]);

    SetAsZero(vecZero);

    start = clock();
    Jacobi(vecZero, &iterations);
    end = clock();
    printf("For Jacobi method, %d iterations were performed, execution time: %.3f  \n", iterations, (double)(end - start)/CLOCKS_PER_SEC);

    for(int i = 0; i < N; i++)
        fprintf(data2, "%i\t %.10lf \n", i, vecZero[i]);

    SetAsZero(vecZero);

    start = clock();
    GausSeidle(vecZero, &iterations);

    
    end = clock();
    printf("For Gauss-Seidel method, %d iterations were performed, execution time: %.3f  \n", iterations, (double)(end - start) /CLOCKS_PER_SEC);

    for(int i = 0; i < N; i++)
        fprintf(data3, "%i\t %.10lf \n", i, vecZero[i]);

        SetAsZero(vecZero);

         start= clock();
   SuccesiveOverRelaxaton(vecZero,&iterations,1.993);
    end = clock();
    printf("dla SOR przeszlo %i razy, czas wykonywania programu wyniosl: %.3f  \n", iterations,(double)(end - start)/CLOCKS_PER_SEC);

    for(int i = 0; i < N; i++)
        fprintf(data4, "%i\t %.10lf \n", i, vecZero[i]* Diagonal);

}

