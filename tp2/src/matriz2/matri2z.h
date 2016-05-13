#ifndef __Matriz_H_INCLUDED__   //   #define this so the compiler knows it has been included
#define __Matriz_H_INCLUDED__   //   #define this so the compiler knows it has been included

class Matriz {
    private:
        int f; // N Filas
        int c; // M Columnas
        double** matrix;
        bool tr;
        bool posicionValida(int x, int y) const ;

    public:
    	//Tengo que arreglar todas;
        Matriz(int a, int b); // Hecha
        Matriz(const Matriz& other); //  Creo que esta
        Matriz operator*(Matriz& a); // Hecha
        Matriz operator+(Matriz& a); // Operacion +
        Matriz operator-(Matriz& a); // Falta esta y la suma
        bool operator==(Matriz& a); // Esta Tambien ;
        ~Matriz(); // Never Changed
        int getF() const; // Done
        int getC() const; // Done
        double** getMatrix();// Nunca la tuve que cambiar;
        void setVal(int x, int y, double val); // Hecha
        void T(); // Hecha
        double getVal(int x, int y) const ; // Hecha
        void printM(); // Hecha
        double ProductoInterno(Matriz& a,Matriz& b,int f,int c);
};
#endif
