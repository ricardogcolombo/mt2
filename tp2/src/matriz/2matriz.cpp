#include "matriz.h"

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;



Matriz::Matriz(int a,int b) {
    n = a; // N FILAS y M COLUMNAS
    m = b;
    matrix = new double*[n];
    //inicializo la matriz de cocmanera segura (evitando problemas de manejo de memoria)
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

void Matriz::T()
{
/*	int oldn = this->n;
	int oldm = this->m;
	Basicamente es C&P del constructor 
	exceptuando la parte de poner valores
	
	this->n=oldm;

	this->m=oldn;

	matrix = new double*[n];
    
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = this->getVal(j,i);
        }
    }
	this->matrix=matrix;
*/	

	
}

Matriz Matriz::operator*(Matriz& a)
{	//Falta el if para ver si coniciden los dimensiones
	n=this->getN();
	m=a.getM();
	Matriz res = Matriz(n,m);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			/*double temp = ProductoInterno(*this,a,i,j);*/
			res.setVal(i,j,ProductoInterno(*this,a,i,j));
		}
	}
	
	return res;
}

double Matriz::ProductoInterno(Matriz& a , Matriz& b, int f , int c) 
{	double res = 0 ;
	//Columnas
	int contandor = b.getN();
	for (int i = 0; i < contandor; ++i)
	{
		res += a.getVal(f,i)*b.getVal(i,c);
	}
return res;


}


Matriz::Matriz(const Matriz& other) // Constructor por copia
{ 
	n = other.getN();
	m = other.getM();
	matrix = new double*[n];
    //For de crear los arrays
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = other.getVal(i,j);
        }
    }
    //For de copiar los valores

}

    


Matriz::~Matriz() {
    for (int i = 0; i <n ; i++) {
        delete[] matrix[i];
        // delete matrix[i];
    }
    delete[] matrix;
    //delete matrix;
}

/**
 * matrix getter
 */

double** Matriz::getMatrix() {
    return matrix;
}

/**
 * n getter
 */

int Matriz::getN() const {
    return n;
}

/**
 * m getter
 */

int Matriz::getM() const  {
    return m;
}

/**
 * Obtener el valor de la matriz en un punto
 *
 * @param {int} x
 * @param {int} y
 *
 * @return {double} m(x, y)
 *
 * x1   x2  0   0   0
 * x3   x4  x5  0   0
 * 0    x6  x7  x8  0
 * 0    0   x9  x10 x11
 *
 * Para ahorrar los 0s lo transformo en =>
 * x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11
 */

double Matriz::getVal(int x, int y) const  {
    if (posicionValida(x, y)) {
        return matrix[x][y];
    } else {
        return 0.0;
    }
}

/**
 * Setear valor en un punto
 *
 * @param {int} x
 * @param {int} y
 * @param {double} valor a setear
 */

    void Matriz::setVal(int x, int y, double val) {
        if (posicionValida(x, y)) {
            matrix[x][y] = val;
        } else {
            // Si x, y están fuera de rango tira una excepcion
            cout << "Intento de seteo en cordenadas: (" << x << "," << y << ")" << endl;
            throw 0;
        }
    }

/**
 * Devuelve true si x e y forman una posicion valida en la matriz
 *
 * @param {int} x
 * @param {int} y
 *
 * @return {boo} true si es valida, false si no
 *
 * x1   x2  0   0   0   0
 * 0    x5  x6  0   0   0
 * 0    0   x9  x10 0   0
 */

bool Matriz::posicionValida(int x, int y) const  {
    // Si no cumple ninguna de las condiciones previas, es verdadero
    return x<this->getN() && y<this->getM();
}

/**
 * Imprime la matriz de un modo conveniente
 */

void Matriz::printM() 
{
	for (int i = 0; i < this->getN(); ++i)
	{
		for (int j = 0; j < this->getM(); ++j)
		{
			cout << this->getVal(i,j) << "\t";
		}
		cout << "\n";
	}

}


