/* #include "commons.h" */

// //devuelve el mayor autovalor
// vectorNum *metodoDeLasPotencias(Matriz *covarianza) {
  // int dimencion = covarianza->getN();
  // vectorNum *vectorInicial = crearVectorInicial(dimencion);

  // double normaVieja = 0;
  // double norma = 1;

  // while ( abs( normaVieja - norma) > 0.000000000000001) {
    // normaVieja = vectorInicial->norma2();
    // vectorNum *nuevoVector = covarianza->producto(vectorInicial);

    // norma = nuevoVector->norma2();
    // nuevoVector->multiplicacionEscalar((1 / (double)norma));
    // delete vectorInicial;
    // vectorInicial = nuevoVector;
  // }
  // return vectorInicial;
// }
// Matriz *matCovarianza(vector<imagen> &v, vectorNum * medias) {
  // int dimencion = medias->size();
  // Matriz *covarianza = new Matriz(dimencion,dimencion);

  // //Aca nos creamos el X del slide
  // vector<vectorNum*> X;
  // for (int i = 0; i < dimencion; i++) {
    // vectorNum* nuevoVector = new vectorNum(v.size());
    // for (int j = 0; j < v.size(); j++) {
      // nuevoVector->set(j, (double) v[j].vect->get(i) - medias->get(i));
    // }
    // //nuevoVector->print();
    // X.push_back(nuevoVector);
  // }
  // //ahora Armamos la matriz Mx
  // for (int i = 0 ; i < dimencion; i++) {
    // for (int k = 0 ; k < dimencion; k++) {
      // covarianza->setVal(i, k, X[i]->multiplicacionVect(X[k]) / (double)(v.size() - 1 ));
    // }
  // }
  // return covarianza;
// }


// Matriz *matrizDeCovarianza(vector<imagen> &etiquetados) {
  // vectorNum *medias = calcularMedias(etiquetados);
  // Matriz *matrizCovarianza = matCovarianza(etiquetados, medias);
  // delete medias;
  // return matrizCovarianza;
// }

// vectorNum *calcularMedias(vector<imagen> &v) {
  // vectorNum *medias = new vectorNum(v[0].vect->size());
  // for (int j = 0; j < v[0].vect->size(); j++) {
    // double media = 0.0;
    // for (int i = 0; i < v.size(); i++) {
      // media += v[i].vect->get(j);
    // }
    // medias->set(j, (double)media / (double)v.size());
  // }
  // return medias;
// }

// vectorNum *crearVectorInicial(int dim) {
  // vectorNum *vectorInicial = new vectorNum(dim);
  // for (int w = 0; w < dim; w++) {
    // int random = rand() % 100 + 1;
    // vectorInicial->set(w, (double)random);
  // }
  // return vectorInicial;
// }

// void trasponerEntrada(vector<imagen> &etiquetados, std::vector<vectorNum*> &autovectores, int cantidadAutovectores) {
  // for (int j = 0; j < etiquetados.size(); j++) {
    // vectorNum* vectorAux = new vectorNum(cantidadAutovectores);
    // for (int i = 0; i < autovectores.size(); i++) {
      // vectorAux->set(i, autovectores[i]->multiplicacionVect(etiquetados[j].vect));
    // }
    // //Borro el vector viejo y le pongo el de las nuevas dimenciones
    // delete etiquetados[j].vect;
    // etiquetados[j].vect = vectorAux;
  // }
// }

// double encontrarAutovalor(vectorNum * autovector, Matriz * covarianza) {
  // vectorNum * aux = covarianza->producto(autovector);
  // double lamda = aux->norma2();
  // delete aux;
  // return lamda;
/* } */
