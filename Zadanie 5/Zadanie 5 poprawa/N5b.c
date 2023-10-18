#include <stdio.h>
#include <stdlib.h>

#define N 1001

int main() {
    FILE *file;
    file = fopen("wynikb.txt", "w");
    if (!file) {
        printf("Error");
        exit(0);
    }

    double results[N];
    double h = 0.001;
    double h2 = h*h + 2;

    results[0] = 1;
    results[1] = 2 / (2 - h*h);
    results[2] = 4 * results[1] - 3;

    for(int i = 3; i < N ; i++){
        results[i] = results[i - 1] * h2 - results[i - 2];
    }

    for(int i = 0 ; i < N ; i++){
        fprintf (file," %i %.16lf %.16lf \n",i+1 ,i*h, results[i] );
    }
}