#include "plsda.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadIteraciones, int gamma){
//obtengo X
    vectorNum *medias = calcularMedias(etiquetados);
    vector<vectorNum*> X = matX(etiquetados,medias);
// Obtengo Y

}

