#include "commons.h"

vectorNum *metodoDeLasPotencias(Matriz *covarianza) {
    int dimencion = covarianza->getF();
    vectorNum *vectorInicial = crearVectorInicial(dimencion);

    double normaVieja = 0;
    double norma = 1;

    while ( abs( normaVieja - norma) > 0.000000000000001) {
        normaVieja = vectorInicial->norma2();
        vectorNum *nuevoVector = covarianza->multiplicarVector(vectorInicial);
        norma = nuevoVector->norma2();
        nuevoVector->multiplicacionEscalar((1 / (double)norma));
        delete vectorInicial;
        vectorInicial = nuevoVector;
    }
    return vectorInicial;
}

vectorNum *crearVectorInicial(int dim) {
    vectorNum *vectorInicial = new vectorNum(dim);
    for (int w = 0; w < dim; w++) {
        int random = rand() % 100 + 1;
        vectorInicial->set(w, (double)random);
    }
    return vectorInicial;
}

vector<vectorNum*> matX(vector<entrada> &v, vectorNum * medias) {
    int dimension = medias->size();

    //Aca nos creamos el X del slide
    vector<vectorNum*> X;
    for (int i = 0; i < dimension; i++) {
        vectorNum* nuevoVector = new vectorNum(v.size());
        for (int j = 0; j < v.size(); j++) {
            nuevoVector->set(j, (double) v[j].vect->get(i) - medias->get(i));
        }
        //nuevoVector->print();
        X.push_back(nuevoVector);
    }
    return X;
};

Matriz *matCovarianza(vector<entrada> &v, vectorNum * medias) {
    int dimension = medias->size();
    Matriz *covarianza = new Matriz(dimension,dimension);

    //Aca nos creamos el X del slide
    vector<vectorNum*> X = matX(v,medias);
    //ahora Armamos la matriz Mx
    for (int i = 0 ; i < dimension; i++) {
        for (int k = 0 ; k < dimension; k++) {
            covarianza->setVal(i, k, X[i]->multiplicacionVect(X[k]) / (double)(v.size() - 1 ));
        }
    }
    return covarianza;
}
void trasponerEntrada(vector<entrada> &etiquetados, std::vector<vectorNum*> &autovectores, int cantidadAutovectores) {
    for (int j = 0; j < etiquetados.size(); j++) {
        vectorNum* vectorAux = new vectorNum(cantidadAutovectores);
        for (int i = 0; i < autovectores.size(); i++) {
            vectorAux->set(i, autovectores[i]->multiplicacionVect(etiquetados[j].vect));
        }
        //Borro el vector viejo y le pongo el de las nuevas dimenciones
        delete etiquetados[j].vect;
        etiquetados[j].vect = vectorAux;
    }
}

Matriz* multiplicacionVectTrans2(vectorNum* unVector, vectorNum *otroVector) {
    int dim = otroVector->size();
    if(unVector->size() != dim)
        throw -1;
    Matriz * matriz = new Matriz(dim,dim);
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            matriz->setVal(i,j, unVector->get(i)*otroVector->get(j));
    return matriz;
}

double encontrarAutovalor(vectorNum * autovector, Matriz * m) {
    vectorNum * aux = m->multiplicarVector(autovector);
    double lamda = aux->norma2();
    delete aux;
    return lamda;
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
