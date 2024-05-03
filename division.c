#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long int A;
    long long int B;
    long long int K;
    long long int R;
}Bezout;

void darNumeros(long long int * a, long long int * b);
void division(long long int a, long long int b, long long int *k, long long int *r);
void mostrarDivision(long long int a, long long int b, long long int k, long long int r);
long long int euclides(long long int a, long long int b, long long int k, long long int r, int * n);
void bIgualCero(long long int b);
//Cosas para Bezout
void mostrarOperaciones(Bezout *B1, int n);
Bezout * crearEstructura(int n);
void euclidesParaBezout(long long int a, long long int b, long long int k, long long int r, Bezout * B1);
void algoritmoBezout(Bezout *B1, long long int mcd, int n);

int main(){
    long long int a,b,k,r,mcd;
    //Valor máximo para un long long int es 9,223,372,036,854,775,807. (19 cifras)
    Bezout *B1;
    int n;
    
    darNumeros(&a,&b);
    bIgualCero(b);

    printf("----- ALGORITMO DE DIVISION -----\n");
    division(a,b,&k,&r);
    mostrarDivision(a,b,k,r);
    printf("k = %lld, r = %lld\n",k,r);
    

    printf("----- ALGORITMO DE EUCLIDES -----\n");
    mcd = euclides(a,b,k,r,&n);
    printf("Se realizaron un total de %d divisiones.\n",n);
    printf("mcd(%lld,%lld)= %lld\n",a,b,mcd);

    printf("----- ALGORITMO DE BEZOUT -----\n");
    B1 = crearEstructura(n);
    euclidesParaBezout(a,b,k,r,B1);
    mostrarOperaciones(B1,n);
    algoritmoBezout(B1,mcd,n);
    free(B1);

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

long long int euclides(long long int a, long long int b, long long int k, long long int r, int * n){
    long long int aOG=a, bOG=b, mcd;
    int divisiones = 0;
    
    if(a == 0 || r == 0){
        //Si el a o el residuo de la division fue 0, entonces b seria el mcd
        mcd = b;
    }else{
        while (r > 0){
            mcd = r;
            divisiones++;
            division(a,b,&k,&r);
            mostrarDivision(a,b,k,r);
            a = b;
            b = r; 
        }
    }
    
    *n = divisiones;

    return mcd;
}

void euclidesParaBezout(long long int a, long long int b, long long int k, long long int r, Bezout * B1){
    long long int aOG=a, bOG=b, mcd;
    int i=0;
    
    if(a == 0 || r == 0){
        //Si el a o el residuo de la division fue 0, entonces b seria el mcd
        mcd = b;
    }else{
        while (r > 0){
            mcd = r;
            division(a,b,&k,&r);
            /**Asignaciones Bezout**/
            B1[i].A = a;
            B1[i].B = b;
            B1[i].K = k;
            B1[i].R = r;
            i++;
            /***********************/
            a = b;
            b = r;
        }
    }
}

Bezout * crearEstructura(int n){
    Bezout *nuevo;
    nuevo = (Bezout*)malloc(n * sizeof(Bezout));

    if(nuevo == NULL){
        printf("Error de memoria");
        exit(0);
    }
}

void mostrarOperaciones(Bezout *B1, int n){
    for (int i = 0; i < n; i++){
        printf("[%d]:%lld = %lld(%lld) + %lld\n",i,B1[i].A,B1[i].B,B1[i].K,B1[i].R);
    } 
}

void algoritmoBezout(Bezout *B1, long long int mcd, int n){
    long long int aB, x, bB, y, rB, aOG = B1[0].A, bOG = B1[0].B; 
    int orden = 0;

    rB = B1[n-2].R; /*rB mantendrá su valor*/
    aB = B1[n-2].A;
    x = 1;
    bB = B1[n-2].B;
    y = B1[n-2].K * -1;

    for (int i = n-2; i >= 0; i--){
        if(orden%2 == 0 && orden != 0){
            aB = B1[i].A;
            y -= B1[i].K * x;
        }if(orden%2 != 0){
            aB = B1[i].B;
            x += (-B1[i].K)*y;
            //printf("%lld + %lld * %lld\n",x,-B1[i].K,y);
            bB = B1[i-1].B;
        }
        printf("%d: %lld = %lld(%lld) + %lld(%lld)\n", i, rB, aB, x, bB, y);
        //printf("%lld = %lld(%lld) + %lld(-%lld)\n", B1[i].R, B1[i].A, B1[i].B, B1[i].K);
        orden++;
    }
    printf("mcd(%lld,%lld) = %lld(%lld) + %lld(%lld)\n", aOG, bOG, aOG, x, bOG, y);
}

void bIgualCero(long long int b){
    if (b == 0){
        printf("No se puede dividir entre 0.\n");
        exit(0);
    }
}