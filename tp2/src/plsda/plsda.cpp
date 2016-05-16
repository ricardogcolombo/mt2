#include "plsda.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, fstream &myfile, int cantidadIteraciones,Matriz * X2_t){
    std::vector<vectorNum*> autovectores;
    //Matriz de Covarianza de X
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
        vectorNum * wi = metodoDeLasPotencias(X_t);
        autovectores.push_back(wi);

        // normalizo el autovector
        double lamda = encontrarAutovalor(wi, X_t);
        myfile << lamda << endl;

        double norma2Autovector=  wi->norma2();
        wi->multiplicacionEscalar((1/(double)norma2Autovector));
        // obtengo ti = X * autovector
        vectorNum *t_i = X->multiplicarVector(wi);

        // normalizo ti
        double norma2t_i=  t_i->norma2();
        t_i->multiplicacionEscalar((1/(double)norma2t_i));

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

Matriz *preY(vector<entrada> t){
    Matriz *n = new Matriz(t.size(),10);
    for(int i=0;i<t.size();i++){
        for(int j=0;j<10;j++){
            if(t[i].label-1==j-1){
                n->setVal(i,j,(double)1.0);
            }else{
                n->setVal(i,j,(double)-1.0);
            }
        }
    }
    return n;
}


double getMean(Matriz* t,int fila){
    double result = 0.0;
    for(int i=0;i<t->getF();i++){
        for(int j=0;j<t->getC();j++){
            result += t->getVal(i,j);
        }
    }
    double total = t->getF()*t->getC() +0.0;
    return result/total;
}
