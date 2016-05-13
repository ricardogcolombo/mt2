#include "testMatriz.h"

void testMatriz(){
    Matriz * t = new Matriz(4,4);
    int i,j;
    int s = 1;
    for(i = 0;i<t->getF();i++){
        for (j = 0; j < t->getC(); j++) {
            t->setVal(i,j,s);
            s++;
        }
    }
    t->printM();
}
