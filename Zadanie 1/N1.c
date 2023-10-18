#include <stdio.h>
#include <math.h>

int main(){

    int x = 1 ;
    int wartosc_x = x*x*x*x;
    double wynik = 0;
    double cos0 = cos(0); //wywołanie dla cos = 0
    double cos1 = cos(wartosc_x); //wywołanie dla cos = 1
    double sin0 = sin(0); //wywołanie dla sin = 0
    double sin1 = sin(wartosc_x); //wywołanie dla sin = 1
    double expon = exp(-1*x); //wywołanie e
    double sinus,cosinus;
    double expon_pom = expon*expon;

    wynik += cos0; //dodajemy wartosci dla n = 0
    wynik += sin1*sin1*expon + cos1*expon*expon*expon*expon; //dodajemy wartości dla n = 1

    cos0 = cos1;
    sin0 = sin1;

    for(int i=2;i<=20;i++){

        sinus = sin0*cos1 + sin1*cos0;  //wykorzystujemy zależności trygonometryczne dla sumy kątów dla sin
        cosinus = cos0*cos1 - sin0*sin1; //wykorzystujemy zależności trygonometryczne dla sumy kątów dla cos

        wynik += (sinus*sinus*expon_pom) + (cosinus*expon_pom*expon_pom*expon_pom*expon_pom); //obliczanie sumy z użyciem własnych zmiennych 

        cos1 = cosinus; //zamiana cos na kolejne iteracje
        sin1 = sinus; //zamiana sin na kolejne iteracje 
        expon_pom *= expon; //zwiększanie exponenty na kolejne iteracje
    } 
    printf("%.9f",wynik);
    
}

