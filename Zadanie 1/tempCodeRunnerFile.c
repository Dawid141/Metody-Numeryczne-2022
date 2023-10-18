#include <stdio.h>

int main(){
    int a[] = {113,2392,12189,70,-31,122,9007,-523,-9,-33};
    int x;
    int n = 10;
    int porownanie = 0;
for (int i=1; i<n; i++){
    for (int j=n-1; j>=i; j--)
    {
        if (a[j-1] >a[j])
        { //zamiana
        porownanie++;
            x=a[j-1];
            a[j-1]=a[j];
            a[j]=x;
        }
    }
}
for(int i=0;i<n;i++){
    printf("%i \n",a[i]);
}
printf("%i \n",porownanie);
}

//rosnaca 0
//malejaco 45
