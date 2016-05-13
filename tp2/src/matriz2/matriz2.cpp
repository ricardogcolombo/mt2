#include "matriz2.h"

#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;



Matriz::Matriz(int a,int b) {
	tr= false;
    f = a; // N FILAS y M COLUMNAS
    c = b;
    matrix = new double*[f];
    //inicializo la matriz de cocmanera segura (evitando problemas de manejo de memoria)
    for (int i = 0; i <f ; i++) {
        matrix[i] = new double[c];
        for (int j = 0; j < c; j++) {
            matrix[i][j] = 0.0;
        }
    }
}


Matriz Matriz::operator+(Matriz& a)
{
	if (this->getF()!=a.getF() || this->getC()!=a.getC())
	{
		cout << "Fijate las dimesiones.." << endl;
		throw 0 ;
	}
	
	f = this->getF();
	c = this->getC();
	Matriz res = Matriz(f,c);

	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			double value = this->getVal(i,j) + a.getVal(i,j);
			res.setVal(i,j,value);
		}
	}

	return res;

}

Matriz Matriz::operator-(Matriz& a)
{
	if (this->getF()!=a.getF() || this->getC()!=a.getC())
	{
		cout << "Fijate las dimesiones.." << endl;
		throw 0 ;
	}
	
	f = this->getF();
	c = this->getC();
	Matriz res = Matriz(f,c);

	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			double value = this->getVal(i,j) - a.getVal(i,j);
			res.setVal(i,j,value);
		}
	}

	return res;
}

bool Matriz::operator==(Matriz& a)
{

	if (this->getF()!=a.getF() || this->getC()!=a.getC())
	{
		return false;
	}

	
	for (int i = 0; i < this->getF(); ++i)
	{
		for (int j = 0; j < this->getC(); ++j)
		{
			if (this->getVal(i,j)	!= a.getVal(i,j) )
			{
				return false;
			}
		}
	}

	return true;
}

Matriz Matriz::operator*(Matriz& a)
{
	//Aca viene el if que chequea si se pueden multlipicar las matrices
		if (this->getC()!=a.getF())
		{
			cout << "Pibe me pasate dos matrices que no se pueden multiplicar " << endl;
			cout << "En ese orden , anda a ver que haces con GDB" << endl;
			throw 0 ;
		}


	//tr = false;
	f=this->getF();
	c=a.getC();
	Matriz res = Matriz(f,c);
	for (int i = 0; i < f; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			//double temp = ProductoInterno(*this,a,i,j);
			res.setVal(i,j,ProductoInterno(*this,a,i,j));
		}
	}
	
	return res;
}

double Matriz::ProductoInterno(Matriz& a , Matriz& b, int f , int c) 
{	double res = 0.0 ;
	int contandor = b.getF();
	for (int i = 0; i < contandor; ++i)
	{
		res += a.getVal(f,i)*b.getVal(i,c);
	}
return res;


}


Matriz::Matriz(const Matriz& other) // Constructor por copia
{ 
	//Quiero que la copie la tal cual esta other en memoria
	tr = other.tr;
	f = other.f;
	c = other.c;
	matrix = new double*[f];
    for (int i = 0; i < f; i++) 
    {
    	matrix[i] = new double[c];
    	for (int j = 0; j < c; j++) 
    	{
           	matrix[i][j] = other.matrix [i][j];
       	}
    }
    

}
    

Matriz::~Matriz() {
    for (int i = 0; i <f ; i++) {
        delete[] matrix[i];
        // delete matrix[i];
    }
    delete[] matrix;
    //delete matrix;
}


double** Matriz::getMatrix() {
    return matrix;
}

int Matriz::getF() const 
{
	if (this->tr)
	{
		return c ;
	}
	return f;
}


int Matriz::getC() const  
{
    if (this->tr)
	{
		return f ;
	}
	return c;
}



double Matriz::getVal(int x, int y) const  
{

	if (posicionValida(x, y))
		{
				if (this->tr){return matrix [x][y];}
				else{return matrix [y] [x];}
		}

	else
	{
		cout << "Pibe me pediste posicion invalida" << endl;
		cout << "Anda a ver que hiciste" << endl;
		return 0.0;
	}


}

void Matriz::T()
{
	this->tr =!this->tr;

}

void Matriz::setVal(int x, int y, double val) 
{
		if (posicionValida(x,y))
		{
			if (tr==false)
			{
				 matrix [x] [y] = val;
			}
			else
			{
				matrix [y] [x] = val ;
			}

		}
		else
		{
			cout << "Pibe anda a debugear que queres escribir una posicion fruta" << endl;
			throw 0;
		}

}


// X es la fila e y la Columna a ver si estan en rango
bool Matriz::posicionValida(int x, int y) const  
{
	return x<this->getF() && y<this->getC();
}

void Matriz::printM() 
{
	for (int i = 0; i < this->getF(); ++i)
	{
		for (int j = 0; j < this->getC(); ++j)
		{
			cout << this->getVal(i,j) << "\t";
		}
		cout << "\n";
	}

}


