#include "testMatriz.h"

void testMatriz(){
    Matriz * t = new Matriz(784,37800);
    int i,j;
    int s = 1;
    for(i = 0;i<t->getF();i++){
        for (j = 0; j < t->getC(); j++) {
            t->setVal(i,j,s);
            s++;
        }
    }
    Matriz * unos  = new Matriz(37800,10);
    for(i = 0;i<unos->getF();i++){
        for (j = 0; j < unos->getC(); j++) {
            unos->setVal(i,j,2);
        }
    }

    cout <<t->getF()<< " "<< t->getC()<<endl;
    cout << unos->getF()<< " "<< unos->getC()<<endl;

    t->multiplicarMatriz(unos);
    cout<< t->getF() << " " << t->getC()<< endl;

}

