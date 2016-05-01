#ifndef _PCA_H
#define _PCA_H
#include "../instancia/instancia.h"
#include "../matriz/matriz.h"


void calcularPca(vector<imagen> &etiquetados, vector<imagen> &sinEtiquetar, fstream &myfile, int cantidadAutovectores);


#endif
