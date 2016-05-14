#include "testMatriz.h"

void testMatriz(){
    Matriz * t = new Matriz(30,10);
    int i,j;
    int s = 1;
    for(i = 0;i<t->getF();i++){
        for (j = 0; j < t->getC(); j++) {
            t->setVal(i,j,s);
            s++;
        }
    }
    Matriz * unos  = new Matriz(*t);

    unos->trasponer();

    cout <<t->getF()<< " "<< t->getC()<<endl;
    cout << unos->getF()<< " "<< unos->getC()<<endl;

    t->multiplicarMatriz(unos);
    cout<< "funco"<< endl;

}
