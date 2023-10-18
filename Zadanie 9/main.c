#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-8  // dokładność, jaką chcemy osiągnąć
#define N 3
#define MAX_ITERATION 1000000

double vectorTimesVector(double *u, double *v){
    double result = 0.0;

    for(int i = 0; i < N; i++){
        result += (u[i] * v[i]);
    }
    return result;
}

double norm(double *u){
    return sqrt(vectorTimesVector(u, u));
}

void matrixTimesVector(double matrix[N][N], double* v, double* result){
    for(int i = 0; i < N;i++){
        result[i] = 0;

        for(int j = 0; j < N; j++){
            result[i] += matrix[i][j] * v[j];
        }
    }
}

void vectorTimesVectorMatrix(double* v, double* y, double matrix[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matrix[i][j] = v[i] * y[j];
        }
    }
}

void matrixTimesMatrix( double matrix[N][N], double matrix2[N][N],double result[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
           result[i][j] = 0.0;

           for(int k = 0; k < N; k++){
            result[i][j] += matrix[i][k] * matrix2[k][j];
           }
        }
    }
}

void powerMethod(double matrix[N][N], double* v, double *lambda){
    double y[N];
    double newLambda;
    int j;

    for(int i = 0; i < MAX_ITERATION; i++){
        matrixTimesVector(matrix, v, y);
        newLambda = vectorTimesVector(v,y) / vectorTimesVector(v, v);

        if(fabs(newLambda - *lambda) < EPSILON){
            *lambda = newLambda;
            return;
        }

        *lambda = newLambda;

        for(j = 0; j < N; j++){
            v[j] = y[j] / norm(y);
        }
    }
}

void rayLeight(double matrix[N][N], double *v, double * lambda){
    double y[N];
    double newLambda;
    int j;

    for(int i = 0; i < MAX_ITERATION; i++){
        matrixTimesVector(matrix, v, y);
        *lambda = vectorTimesVector(v, y) / vectorTimesVector(v,v);

        newLambda = vectorTimesVector(y, y) / vectorTimesVector(y, v);
        if(fabs(*lambda - newLambda) < EPSILON){
            return;
        }

        for(j = 0; j < N; j++){
            v[j] = y[j] / norm(y);
        }
    }
}

void QRdecomposition(double matrix[N][N], double * result){
   
   int i,j;
   double Q[N][N] = {0.0};
   double R[N][N] = {0.0};
   double results[N][N] = {0.0};

   for(j = 0; j < N; j++){
    Q[j][j] = 1.0;
    R[j][j] = 1.0;
   }
   double House[N][N] = {0.0};
   

   for(j = 0; j < MAX_ITERATION; j++){
        for(i = 0; i < N - 1; i++){
            double v[N] = {0.0};

            for(int k = i; k < N ; k++){
                v[k] = matrix[i][k];
            }

            v[i] += norm(v);


            double vvT[N][N];
            vectorTimesVectorMatrix(v, v, vvT);

            //H matrix
            double House[N][N] = {0.0};
            double temp = 2 / vectorTimesVector(v, v);

            for(int k = 0; k < N; k++){
                for(int l = 0; l < N; l++){
                    if(k == l){
                        House[k][l] += 1;
                    }
                    House[k][l] -= temp * vvT[k][l];
                }
            }

            matrixTimesMatrix(House,matrix,R);
            matrixTimesMatrix(Q,House, results);

            for(int k = 0; k < N; k++){
                for(int l = 0; l < N; l++){
                    Q[k][l] = results[k][l];
                    matrix[k][l] = R[k][l];
                }
            }
        }
       
        matrixTimesMatrix(R, Q, matrix);
   }

   for(int i = 0; i < N; i++){
    result[i] = matrix[i][i];
   }
}


void SetAsZero (double vector[N]){
    for(int i = 0; i < N; i++){
        vector[i] = 1.0;
    }
}

int main() {
    // Przykładowa macierz 3x3
    double mat[N][N] = { {1, 2, 3},
                      {2, 4, 5},
                      {3, 5, -1} };

    double x[N] = {1};
    double pom = 0;

printf("Metoda potegowa: \n");

    powerMethod(mat, x, &pom);
    printf("najwieksza wartosc wlasna macierzy to : %lf. \n", pom);
    printf("wektor wlasny: ");
    for(int i = 0; i < N; i++){
        if(i != N){
            printf("%lf, ", x[i]);
        }
        
    }
    SetAsZero(x);

    printf("Metoda rayleighta: \n");

    rayLeight(mat, x, &pom);
    printf("najwieksza wartosc wlasna macierzy to : %lf. \n", pom);
    printf("wektor wlasny: ");
    for(int i = 0; i < N; i++){
        if(i != N){
            printf("%lf, ", x[i]);
        }
        
    }

printf("Metoda QR: \n");

     QRdecomposition(mat, x);
    printf("wektor wlasny: ");
    for(int i = 0; i < N; i++){
        if(i != N){
            printf("%lf, ", x[i]);
        }
        
    }
}