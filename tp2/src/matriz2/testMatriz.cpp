#include "testMatriz.h"

void testMatriz(){
    Matriz * t = new Matriz(4,4);
    Matriz * unos  = new Matriz(4,4);
    Matriz * dos = new Matriz(4,4);
    int i,j;
    int s = 1;
    for(i = 0;i<t->getF();i++){
        for (j = 0; j < t->getC(); j++) {
            t->setVal(i,j,s);
            unos->setVal(i,j,1);
            dos->setVal(i,j,2);
            s++;
        }
    }
    t->printM();
    cout<<endl;

    t->trasponer();
    t->printM();
    cout<<endl;

    t->multiplicarMatriz(dos);
    t->printM();
    cout<<endl;
}
