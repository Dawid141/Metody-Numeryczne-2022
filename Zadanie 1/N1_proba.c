#include <stdio.h>
#include <math.h>

double funkcja(int x, int n){

return(pow(sin(n*pow(x,4)),2)*exp(-n)+cos(n*pow(x,4))*exp(-4*n));

}

int main(){
double wynik = 0;
int n;

for(int i = 0 ;i < 23; i++){

    wynik += funkcja(1,i);
    printf("%.10f \n",wynik);
}

}