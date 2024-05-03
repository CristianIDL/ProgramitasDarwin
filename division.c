#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long int a;
    long long int b;
    long long int k;
    long long int r;
}Bezout;


void darNumeros(long long int * a, long long int * b);
void division(long long int a, long long int b, long long int *k, long long int *r);
void mostrarDivision(long long int a, long long int b, long long int k, long long int r);
long long int euclides(long long int a, long long int b, long long int k, long long int r);
void bIgualCero(long long int b);

int main(){
    long long int a,b,k,r,mcd;
    Bezout *B1;
    //Valor máximo para un long long int es 9,223,372,036,854,775,807. (19 cifras)
    
    darNumeros(&a,&b);
    bIgualCero(b);

    printf("----- ALGORITMO DE DIVISION -----\n");
    division(a,b,&k,&r);
    mostrarDivision(a,b,k,r);
    printf("k = %lld, r = %lld\n",k,r);
    

    printf("----- ALGORITMO DE EUCLIDES -----\n");
    mcd = euclides(a,b,k,r);
    printf("mcd(%lld,%lld)= %lld",a,b,mcd);

    return 0;
}

void darNumeros(long long int * a, long long int * b){
    printf("Da el valor para a:\n");
    scanf("%lld", a);
    printf("Da el valor para b:\n");
    scanf("%lld", b);
}

void division(long long int a, long long int b, long long int *k, long long int *r){
    long long int contador = 0, residuo = a, papubandera=0; //cuenta la cantidad de veces que se efectua la resta (k)
    *k = 0, *r = 0;
    
    if(a > 0){
        if (b<0){
            b *= -1;
            papubandera = 1;
        }
        while (a >= b){
            a -= b;
            contador++;
            //printf("a=%lld, b=%lld, k=%lld\n",a,b,contador);
        }
        if (papubandera == 1)
            contador *= -1;

        residuo = a;
    }
    if(a < 0){
        if (b<0){
            b *= -1;
            papubandera = 1;
        }
        while ((contador * b) > a){
            contador--;
            residuo += b;
            //printf("Caso a<0 a=%lld, b=%lld, k=%lld\n",a,b,contador);
        }
        if (papubandera == 1)
            contador *= -1;
    }
    
    *k = contador;
    *r = residuo;
}

void mostrarDivision(long long int a, long long int b, long long int k, long long int r){
    printf(" %lld = %lld(%lld) + %lld\n",a,b,k,r);
}

long long int euclides(long long int a, long long int b, long long int k, long long int r){
    long long int aOG=a, bOG=b, mcd;
    
    if(a == 0 || r == 0){
        //Si el a o el residuo de la division fue 0, entonces b seria el mcd
        mcd = b;
    }else{
        while (r > 0){
            mcd = r;
            division(a,b,&k,&r);
            mostrarDivision(a,b,k,r);
            a = b;
            b = r; 
        }
    }
    
    return mcd;
}

void bezout(){
    
}

void bIgualCero(long long int b){
    if (b == 0){
        printf("No se puede dividir entre 0.\n");
        exit(0);
    }
}