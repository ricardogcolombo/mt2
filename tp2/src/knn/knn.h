#ifndef _KNN_H
#define _KNN_H


#include "../instancia/instancia.h"
#include "../vector/vectorNum.h"

using namespace std;

void calcularknn(vector<imagen> &etiquetados, vector<imagen> &sinEtiquetar, int cantidadDeVecinosMasCercanos);


#endif
