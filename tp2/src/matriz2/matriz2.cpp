#include "matriz2.h"

using namespace std;

Matriz::Matriz(int a,int b) {
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

void Matriz::LimpiarMemoria()
{
	for (int i = 0; i < this->getF(); ++i)
	{
		delete[] this->matrix[i];
	}
	
	delete[] this->matrix;
}

// no pude usar operartor *
void Matriz::multiplicarMatriz(Matriz* a){
    // TODO CHECK DIMENSIONES
    int oldf = f;
    int oldc = c;
    double ** oldMatrix = matrix;
    double ** nuevaMatrix = new double*[f];
    int newC = a->getC();
    int aFilas= a->getF();
    for (int i = 0; i < f; i++) {
        nuevaMatrix[i] = new double[newC];
        for (int j = 0; j < newC; j++) {
            double res = 0;
            for (int s = 0; s < aFilas; s++) {
                res += this->getVal(i,s)* a->getVal(s,j);
            }
            nuevaMatrix[i][j]=res;
        }
    }
    c = newC;
    for (int i = 0; i < oldf; ++i)
    {
    	delete[] oldMatrix[i];
    }
    delete[] oldMatrix;
    matrix = nuevaMatrix;
}
// no pude usar el operator -
void Matriz::restarMatriz(Matriz* a){
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            matrix[i][j]=matrix[i][j]-a->getVal(i,j);
        }
    }
}

vectorNum* Matriz::multiplicarVector(vectorNum* unVector){
    int dim = unVector->size();

    if(unVector->size() != dim)
        throw -1;
    vectorNum *vectAux = new vectorNum(f);
    for(int i = 0; i < f; i++){
        double aux = 0;
        for(int j = 0; j < dim; j++)
            aux += unVector->get(j)*matrix[i][j];
        vectAux->set(i, aux);
    }
    return vectAux;
}

Matriz Matriz::operator+(Matriz& a)
{
    if (this->getF()!=a.getF() || this->getC()!=a.getC()) {
        cout << "Fijate las dimesiones.." << endl;
        throw 0 ;
    }

    f = this->getF();
    c = this->getC();
    Matriz res = Matriz(f,c);

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            double value = this->getVal(i,j) + a.getVal(i,j);
            res.setVal(i,j,value);
        }
    }

    return res;

}

Matriz Matriz::operator-(Matriz& a)
{
    if (this->getF()!=a.getF() || this->getC()!=a.getC()) {
        cout << "Fijate las dimesiones.." << endl;
        throw 0 ;
    }

    f = this->getF();
    c = this->getC();
    Matriz res = Matriz(f,c);

    for (int i = 0; i < f;i++) {
        for (int j = 0; j < c; j++) {
            double value = this->getVal(i,j) - a.getVal(i,j);
            res.setVal(i,j,value);
        }
    }

    return res;
}



bool Matriz::operator==(Matriz& a)
{

    if (this->getF()!=a.getF() || this->getC()!=a.getC()) {
        return false;
    }

    for (int i = 0; i < this->getF(); i++) {
        for (int j = 0; j < this->getC(); j++) {
            if (this->getVal(i,j)   != a.getVal(i,j) ) {
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
        cout << "Las  matrices no se pueden multiplicar " << endl;
        throw 1 ;
    }


    //tr = false;
    f=this->getF();
    c=a.getC();
    Matriz res = Matriz(f,c);
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            //double temp = productoInterno(*this,a,i,j);
            res.setVal(i,j,productoInterno(*this,a,i,j));
        }
    }

    return res;
}

double Matriz::productoInterno(Matriz& a , Matriz& b, int f , int c) {
    double res = 0.0 ;
    int contandor = b.getF();
    for (int i = 0; i < contandor; i++) {
        res += a.getVal(f,i)*b.getVal(i,c);
    }
    return res;
}

// Constructor por copia
Matriz::Matriz(const Matriz& other)  {
    //Quiero que la copie la tal cual esta other en memoria
    f = other.f;
    c = other.c;
    matrix = new double*[f];

    for (int i = 0; i < f; i++) {
        matrix[i] = new double[c];
        for (int j = 0; j < c; j++) {
            this->setVal(i,j ,other.getVal(i,j));
        }
    }
}


Matriz::~Matriz() {

    for (int i = 0; i <f ; i++) {
        //delete[] matrix[i];
         delete matrix[i];
    }
    //delete[] matrix;
    delete matrix;
}


double** Matriz::getMatrix() {
    return matrix;
}

int Matriz::getF() const
{

    return f;
}


int Matriz::getC() const
{

    return c;
}



double Matriz::getVal(int x, int y) const {

    if (posicionValida(x, y)) {
        return matrix [x][y];
    } else {
        cout << "get Posicion Invalida" << x <<" "<< y<< endl;
        throw 1;
    }


}


void Matriz::setVal(int x, int y, double val) {
    if (posicionValida(x,y)) {
        matrix [x] [y] = val;

    } else {
        cout << "set Posicion Invalida" << x <<" "<< y<< endl;
        throw 0;
    }
}


// X es la fila e y la Columna a ver si estan en rango
bool Matriz::posicionValida(int x, int y) const {
    return x<this->getF() && y<this->getC();
}

void Matriz::printM() {
    for (int i = 0; i < this->getF(); i++) {
        for (int j = 0; j < this->getC();j++) {
            cout << this->getVal(i,j) << "\t";
        }
        cout << "\n";
    }

}

void Matriz::trasponer() {
    int newC = this->getF();
    int newF = this->getC();
    double ** oldMatrix = matrix;
    matrix  = new double*[newF];
    //inicializo la matriz de cocmanera segura (evitando problemas de manejo de memoria)
    for (int i = 0; i <c ; i++) {
        matrix[i] = new double[newC];
        for (int j = 0; j < f; j++) {
            matrix[i][j] = oldMatrix[j][i];
        }
    }
    f = newF;
    c = newC;
    for (int i = 0; i <newC ; i++) {
        delete[] oldMatrix[i];
        // delete matrix[i];
    }
    delete[] oldMatrix;
}

