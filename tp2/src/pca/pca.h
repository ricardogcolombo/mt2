#ifndef _PCA_H
#define _PCA_H
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "../manejoEntrada/entrada.h"
#include "../commons/commons.h"
#include "../matriz/matriz.h"

void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadAutovectores);
vectorNum *calcularMedias(vector<entrada> &v);
matrizNum * matrizDeCovarianza(vector<entrada> &etiquetados);
matrizNum *matCovarianza(vector<entrada> &v, vectorNum *medias);
vectorNum *metodoDeLasPotencias(matrizNum *covarianza);
void trasponerEntrada(vector<entrada> &etiquetados, std::vector<vectorNum*> &autovectores, int cantidadAutovectores);
double encontrarAutovalor(vectorNum *autovector, matrizNum *covarianza);
#endif
