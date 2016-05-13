#include "pca.h"

void calcularPca(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadAutovectores) {
    // calculamos la matriz de covarianza
    matrizNum *covarianza = matrizDeCovarianza(etiquetados);
    std::vector<vectorNum*> autovectores;

    myfile.precision(6);
    myfile << scientific;
    //Empiezo a conseguir autovectores
    for (int i = 0; i < cantidadAutovectores; i++) {
        vectorNum * autovector = metodoDeLasPotencias(covarianza);
        //guardo los actovectores en un vector
        autovectores.push_back(autovector);
        double lamda = encontrarAutovalor(autovector, covarianza);

        myfile << lamda << endl;

        vectorNum *autovectorAux = autovector->copy();
        autovector->multiplicacionEscalar(lamda);
        covarianza->resta(autovector->multiplicacionVectTrans(autovectorAux));
        delete autovectorAux;
    }
    trasponerEntrada(etiquetados, autovectores, cantidadAutovectores);
    trasponerEntrada(sinEtiquetar, autovectores, cantidadAutovectores);

    delete covarianza;
    for (int i = 0; i < autovectores.size(); i++) {
        delete autovectores[i];
    }
}


//devuelve el mayor autovalor
vectorNum *metodoDeLasPotencias(matrizNum *covarianza) {
    int dimencion = covarianza->size();
    vectorNum *vectorInicial = crearVectorInicial(dimencion);

    double normaVieja = 0;
    double norma = 1;

    while ( abs( normaVieja - norma) > 0.000000000000001) {
        normaVieja = vectorInicial->norma2();
        vectorNum *nuevoVector = covarianza->producto(vectorInicial);
        norma = nuevoVector->norma2();
        nuevoVector->multiplicacionEscalar((1 / (double)norma));
        delete vectorInicial;
        vectorInicial = nuevoVector;
    }
    return vectorInicial;
}


matrizNum *matCovarianza(vector<entrada> &v, vectorNum * medias) {
    int dimension = medias->size();
    matrizNum *covarianza = new matrizNum(dimension);

    //Aca nos creamos el X del slide
    vector<vectorNum*> X = matX(v,medias);
    
    //ahora Armamos la matriz Mx
    for (int i = 0 ; i < dimension; i++) {
        for (int k = 0 ; k < dimension; k++) {
            covarianza->set(i, k, X[i]->multiplicacionVect(X[k]) / (double)(v.size() - 1 ));
        }
    }
    return covarianza;
}


matrizNum *matrizDeCovarianza(vector<entrada> &etiquetados) {
    vectorNum *medias = calcularMedias(etiquetados);
    matrizNum *matrizCovarianza = matCovarianza(etiquetados, medias);
    delete medias;
    return matrizCovarianza;
}

vectorNum *calcularMedias(vector<entrada> &v) {
    vectorNum *medias = new vectorNum(v[0].vect->size());
    for (int j = 0; j < v[0].vect->size(); j++) {
        double media = 0.0;
        for (int i = 0; i < v.size(); i++) {
            media += v[i].vect->get(j);
        }
        medias->set(j, (double)media / (double)v.size());
    }
    return medias;
}

double encontrarAutovalor(vectorNum * autovector, matrizNum * covarianza) {
    vectorNum * aux = covarianza->producto(autovector);
    double lamda = aux->norma2();
    delete aux;
    return lamda;
}
