#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define X1 1.0

double dyskretyzacjaA (double x, double h) {
    double wynik = ( (sin( (x + h) ) - sin(x)) / h);
    wynik = wynik - cos(x);

    return fabs(wynik);
}

double dyskretyzacjaB (double x, double h) {
    double wynik = ( ((( sin( (x + h) ) ))-(sin((x-h)))) / (2*h));
    wynik = wynik - cos(x);

    return fabs(wynik);
}

double dyskretyzacjaC (double x, double h) {
    double wynik = (((((-1*(sin( (x + (2*h) ))) + (8*sin((x + h)))) - (8*sin((x - h)))) + sin((x - (2*h))))) / (12*h));
    wynik = wynik - cos(x);

    return fabs(wynik);
}

int main () {
    FILE *file, *file2;
    file = fopen("wyniki.txt", "w");
    if (!file) {
        printf("Error opening file!");
        exit(1);
    }
    file2 = fopen("wyniki2.txt", "w");
    if (!file2) {
        printf("Error opening file2!");
        exit(1);
    }

    double yA, yB, yC;
    fprintf(file, "x\ty1\ty2\ty3\n");
    fprintf(file2, "x\ty1\ty2\ty3\n");
    for (double h = 0.0000000000000001; h <= 1; h = h * 1.0001) {
        yA = dyskretyzacjaA(X1,h);
        yB = dyskretyzacjaB(X1,h);
        yC = dyskretyzacjaC(X1,h);
        
        fprintf(file, "%.16lf\t%.16lf\t%.16lf\t%.16lf\n", h, yA, yB, yC);


        yA = dyskretyzacjaA(M_PI/2,h);
        yB = dyskretyzacjaB(M_PI/2,h);
        yC = dyskretyzacjaC(M_PI/2,h);

        //if(yA > 0.0000000000000001 && yB > 0.0000000000000001 && yC > 0.0000000000000001) {
            fprintf(file2, "%.16lf\t%.16lf\t%.16lf\t%.16lf\n", h, yA, yB, yC);
        //}
    }

    fclose(file);
    fclose(file2);

    return 0;
}