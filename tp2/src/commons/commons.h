

#include "../manejoEntrada/entrada.h"
#include "../vector/vectorNum.h"
#include "../matriz2/matriz2.h"
#ifndef __Commons_H_INCLUDED__   //   #define this so the compiler knows it has been included
#define __Commons_H_INCLUDED__   //   #define this so the compiler knows it has been included



vectorNum *metodoDeLasPotencias2(Matriz *covarianza);
Matriz* multiplicacionVectTrans2(vectorNum *unVector,vectorNum *otroVector);
vectorNum *crearVectorInicial(int dim);
vector<vectorNum *> matX(vector<entrada> &v, vectorNum * medias);
void trasponerEntrada(vector<entrada> &etiquetados, std::vector<vectorNum*> &autovectores, int cantidadAutovectores);
double encontrarAutovalor(vectorNum * autovector, Matriz * m) ;
# endif
