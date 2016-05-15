#ifndef _PLSDA_H
#define _PLSDA_H
#include "../manejoEntrada/entrada.h"
#include "../matriz2/matriz2.h"
#include "../pca/pca.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadIteraciones);
Matriz *preY(vector<entrada> t);
Matriz *fromVectorNumToMatriz(vector<vectorNum*> t);
double getMean(Matriz* t,int fila);
Matriz *vectorTraspuestoToMatriz(vectorNum* t);
#endif
