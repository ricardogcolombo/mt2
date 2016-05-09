#ifndef __Matriz_H_INCLUDED__   //   #define this so the compiler knows it has been included
#define __Matriz_H_INCLUDED__   //   #define this so the compiler knows it has been included

class Matriz {
    private:
        int n; // N Filas
        int m; // M Columnas
        double** matrix;
        bool posicionValida(int x, int y) const ;

    public:
        Matriz(int a, int b);
        Matriz(const Matriz& other); //  Constructor por copia
        Matriz operator*(Matriz& a);
        ~Matriz();
        int getM() const;
        int getN() const;
        double** getMatrix();
        void setVal(int x, int y, double val);
        double getVal(int x, int y) const ;
        void printM();
        void T(); // Me queda esta
        double ProductoInterno(Matriz& a,Matriz& b,int f,int c);
};
#endif
