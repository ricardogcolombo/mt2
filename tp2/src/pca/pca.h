#ifndef _PCA_H
#define _PCA_H
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "../manejoEntrada/entrada.h"
#include "../commons/commons.h"
#include "../matriz/matriz.h"

void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadAutovectores);
Matriz * matrizDeCovarianza(vector<entrada> &etiquetados);
#endif
