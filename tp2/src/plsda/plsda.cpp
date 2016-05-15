#include "plsda.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadIteraciones,Matriz * X2_t){
    std::vector<vectorNum*> autovectores;
    //Matriz de Covarianza de X
    vectorNum *medias = calcularMedias(etiquetados);
    int dimension = medias->size();

    Matriz *X_t = new Matriz(*X2_t);
    //Matriz X traspuesta
    Matriz *X = new Matriz(*X_t);
    X->trasponer();

    //Matriz de Y
    //Aca creo la matriz Y , La voy haciendo de a poco
    Matriz *Y =  preY(etiquetados); //Aca viene la parte de calcular el promedio de todas las filas ??

    double mean = getMean(Y,0) ;

    double root = sqrt(etiquetados.size()-1);
    // Aca el for que transform PreY a Y
    Y->restarYmultiplicarEscalar(mean,root);

    //Copio la Matriz Y con el constructor por copia

    myfile.precision(6);
    myfile << scientific;

    for (int i = 0; i < cantidadIteraciones; i++) {
        // cout << "iteracion numero " << i<<endl;
        // M = X_t Y Y_t X
        X_t->multiplicarMatriz(Y);
        Matriz *Z =new Matriz(*X_t);
        Z->trasponer();
        X_t->multiplicarMatriz(Z);
        delete Z;

        // se supone que aca esta el autovector asociado al mayor autovalor
        vectorNum * autovector = metodoDeLasPotencias(X_t);
        autovectores.push_back(autovector);

        // normalizo el autovector
        double norma2Autovector=  autovector->norma2();
        double lamda = encontrarAutovalor(autovector, X_t);
        myfile << lamda << endl;

        autovector->multiplicacionEscalar(1/norma2Autovector);
        // obtengo ti = X * autovector
        vectorNum *t_i = X->multiplicarVector(autovector);

        // normalizo ti
        double norma2t_i=  t_i->norma2();
        t_i->multiplicacionEscalar(1/norma2t_i);

        // actualizo X = X - ti * ti_t * X
        Matriz * j_t = vectorTraspuestoToMatriz(t_i);
        delete t_i;
        Matriz * j = new Matriz(*j_t);
        j->trasponer();
        Matriz * j2_t = new Matriz(*j_t);
        Matriz * j2 = new Matriz(*j);
        j_t->multiplicarMatriz(X);
        j->multiplicarMatriz(j_t);
        X->restarMatriz(j);

        // actualizo Y = Y - ti * ti_t * Y
        delete X_t;
        // actualizo Z
        X_t = new Matriz(*X);
        X_t->trasponer();

        //  "reste Y-t*ty "
        j2_t->multiplicarMatriz(Y);
        j2->multiplicarMatriz(j2_t);
        Y->restarMatriz(j2);
        delete j;
        delete j_t;
        delete j2;
        delete j2_t;

    }
    delete X;
    delete Y;
    trasponerEntrada(etiquetados, autovectores, cantidadIteraciones);
    trasponerEntrada(sinEtiquetar, autovectores, cantidadIteraciones);
    for (int i = 0; i < autovectores.size(); i++) {
        delete autovectores[i];
    }
}

Matriz *vectorTraspuestoToMatriz(vectorNum* t){
    Matriz * x =  new Matriz(1,t->size());
    for(int i = 0;i<t->size();i++){
        x->setVal(0,i,t->get(i));
    }
    return x;
};

Matriz *fromVectorNumToMatriz(vector<vectorNum*> t){
    int n,m;
    n= t.size();
    m=t[0]->size();
    Matriz* nuevo = new Matriz(n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            nuevo->setVal(i,j,t[i]->get(j));
        }
    }

    return nuevo;
};


Matriz *preY(vector<entrada> t){
    Matriz *n = new Matriz(t.size(),10);
    for(int i=0;i<t.size();i++){
        for(int j=0;j<10;j++){
            if(t[i].label-1==j){
                n->setVal(i,j,1);
            }else{
                n->setVal(i,j,-1);
            }
        }
    }
    return n;
}


double getMean(Matriz* t,int fila){

    double result = 0.0;
    for(int i=0;i<t->getC();i++){
        result += t->getVal(fila,i);
    }
    return result/10.0;
}
