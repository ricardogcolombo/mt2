#ifndef _PLSDA_H
#define _PLSDA_H
#include "../manejoEntrada/entrada.h"
#include "../matriz/matriz.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadIteraciones,int gamma);
#endif
