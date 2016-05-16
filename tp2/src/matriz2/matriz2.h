#ifndef __Matriz2_H_INCLUDED__   //   #define this so the compiler knows it has been included
#define __Matriz2_H_INCLUDED__   //   #define this so the compiler knows it has been included
#include <algorithm>
#include <iostream>
#include <cmath>
#include "../vector/vectorNum.h"

class Matriz {
    private:
        int f; // N Filas
        int c; // M Columnas
        double** matrix;
        bool posicionValida(int x, int y) const ;

    public:
        //Tengo que arreglar todas;
        void LimpiarMemoria();
        Matriz(int a, int b); // Hecha
        Matriz(const Matriz& other); //  Creo que esta
        ~Matriz(); // Never Changed
        int getF() const; // Done
        int getC() const; // Done
        double** getMatrix();// Nunca la tuve que cambiar;
        void setVal(int x, int y, double val); // Hecha
        double getVal(int x, int y) const ; // Hecha
        void printM(); // Hecha
        double productoInterno(Matriz& a,Matriz& b,int f,int c);
        void trasponer();
        void multiplicarMatriz(Matriz* a);
        void restarYmultiplicarEscalar(double m,double t);
        void multiplicarEscalar(double t);
        void restarMatriz(Matriz* a);
        vectorNum *multiplicarVector(vectorNum* a);
};
#endif
