#ifndef __CHOLESKY_H_INCLUDED__   //   #define this so the compiler knows it has been included
#define __CHOLESKY_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include "../Matriz/Matriz.h"
//#include "../instancia/instancia.h"
//#include <iostream>

double* cholesky(double *matriz, int n);
double* cholesky2(Matriz* m ,double *b);

#endif
