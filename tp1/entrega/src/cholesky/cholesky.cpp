#include "../cholesky/cholesky.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

double* cholesky(Matriz* m,double *b){
    int cantFilas = m->getN();
    int i,k,j;
    double *rank = new double[cantFilas];
    double *y= new double[cantFilas];
    Matriz * L = new Matriz(cantFilas,cantFilas);

    // ACA EMPIEZO A GENERAR LA MATRIZ L
    double l11 = sqrt(m->getVal(0,0));
    L->setVal(0,0,l11);

    for (i = 1; i < cantFilas; ++i) {
        double aj1 = m->getVal(i,0);
        double lj1= aj1/l11;
        L->setVal(i,0,lj1);
    }

    for (i = 1; i < cantFilas-1; i++) {

        // lii = aii - sum(k=1,i, lik*likk)
        // step 4
        double aii= m->getVal(i,i);
        double acum = 0.0;
        for (k = 0; k < i; k++) {
            double lik = L->getVal(i,k);
            acum +=  lik*lik;
        }
        L->setVal(i,i,sqrt(aii-acum));
        // step 5
        for (j = i+1;  j< cantFilas; j++) {
            double aux = 0.0;
            double aji = m->getVal(j,i);
            for( k = 0; k < i ; k++){
                double ljk = L->getVal(j,k);
                double lik = L->getVal(i,k);
                aux +=ljk*lik;
            }

            double lji = (aji-aux)/L->getVal(i,i);
            L->setVal(j,i,lji);
        }
    }
    double acum = 0.0;
    for( k = 0; k < cantFilas ; k++){
        acum += L->getVal(cantFilas-1,k)*L->getVal(cantFilas-1,k);
    }
    L->setVal(cantFilas-1,cantFilas-1,sqrt(m->getVal(cantFilas-1,cantFilas-1)-acum));
    // ACA TERMINE DE GENERAR L
    // en L tengo la matriz diagonal inferior de cholesky

    // pasos 8 y 9 del burden L*y= b
    y[0]= b[0]/L->getVal(0,0);

    for (i = 1; i < cantFilas; i++) {
        double acum=0.0;
        for (j = 0; j < i; j++) {
            acum += y[j]*L->getVal(i,j);
        }

        y[i] =( b[i]- acum)/L->getVal(i,i);
    }

    // aca genero x para la salida
    rank[cantFilas-1]= y[cantFilas-1]/L->getVal(cantFilas-1,cantFilas-1);

    for (i = cantFilas-2; i >-1; i--) {
        double acum=0.0;
        for (j = i+1; j < cantFilas; j++) {
            acum += rank[j]*L->getVal(j,i);
        }
        rank[i] =( y[i]- acum)/L->getVal(i,i);
    }
    return rank;
};
