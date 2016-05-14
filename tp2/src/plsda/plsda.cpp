#include "plsda.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadIteraciones, int gamma){
    std::vector<vectorNum*> autovectores;
    //Matriz de Covarianza de X
    vectorNum *medias = calcularMedias(etiquetados);
    int dimension = medias->size();
    //TODO use only Matriz and replace all vector vectornum in pca
    vector<vectorNum*> X1 = matX(etiquetados,medias);
    Matriz *X = fromVectorNumToMatriz(X1);

    //Matriz X traspuesta
    Matriz *X_t = new Matriz(*X);
    X_t->trasponer();

    //Matriz de Y
    //Aca creo la matriz Y , La voy haciendo de a poco
    Matriz *Y =  preY(etiquetados); //Aca viene la parte de calcular el promedio de todas las filas ??

    double mean = getMean(Y,0) ;

    double root = sqrt(etiquetados.size()-1);
    // Aca el for que transform PreY a Y
    for (int i = 0; i < Y->getF(); ++i)
    {
        for (int j = 0; j < Y->getC(); ++j)
        {
            double actual = Y->getVal(i,j);
            Y->setVal(i,j,(actual-mean)/root);
        }
    }

    //Copio la Matriz Y con el constructor por copia

    Matriz* Y_t = new Matriz(*Y);
    Y_t->trasponer() ;

    myfile.precision(6);
    myfile << scientific;

    for (int i = 0; i < cantidadIteraciones; i++) {
        cout << "iteracion numero " << i<<endl;
        Matriz * M= new Matriz(*X_t);
        cout << "multiplico X t por Y" <<endl;
        M->multiplicarMatriz(Y);
        cout << "multiplico X_t*Y por Y_t" <<endl;
        M->multiplicarMatriz(Y_t);
        M->multiplicarMatriz(X);
        cout << "multiplico Y t por Y" <<endl;
        // se supone que aca esta el autovector asociado al mayor autovalor
        vectorNum * autovector = metodoDeLasPotencias2(M);
        autovectores.push_back(autovector);

        // normalizo el autovector
        double norma2Autovector=  autovector->norma2();
        autovector->multiplicacionEscalar(norma2Autovector);
        // obtengo ti = X * autovector
        vectorNum *t_i = X->multiplicarVector(autovector);
        // normalizo ti
        double norma2t_i=  t_i->norma2();
        t_i->multiplicacionEscalar(norma2t_i);

        // actualizo X = X - ti * ti_t * X
        Matriz * j = multiplicacionVectTrans2(t_i,t_i);
        Matriz * j2 = j;

        j->multiplicarMatriz(X);
        X->restarMatriz(j);

        // actualizo Y = Y - ti * ti_t * Y
        j->multiplicarMatriz(Y);
        Y->restarMatriz(j);
    }
    trasponerEntrada(sinEtiquetar, autovectores, cantidadIteraciones);
}

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

    double result = 0;
    for(int i=0;i<t->getC();i++){
        result += t->getVal(fila,i);
    }
    return result;
}
