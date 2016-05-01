#ifndef _PLSDA_H
#define _PLSDA_H
#include "../instancia/instancia.h"
#include "../matriz/matriz.h"

void calcularPLSDA(vector<imagen> &etiquetados, vector<imagen> &sinEtiquetar, fstream &myfile, int cantidadIteraciones);
#endif
