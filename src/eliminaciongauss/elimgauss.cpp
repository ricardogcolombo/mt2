#include <cmath>
#include "elimGauss.h"

using namespace std;
/**
 * Chequea que 2 doubles difieran en menos que un delta
 *
 * @param {double} a
 * @param {double} b
 * @param {double} delta
 *
 * @return {bool} son iguales
 */
bool son_iguales(double a, double b, double delta = 1.0e-10) {
    return abs(a - b) < delta;
}
/**
 * Algoritmo de eliminacion gaussiana
 *
 * @param {MatrizB*} m
 * @param {double*} b
 */
double* gauss(Matriz *m,double * b) {

    //elijo el valor para el pivot
    for (int pivot = 0; pivot < m->getM()-1; pivot++) {


        // por cada fila desde el valor pivot + 1 para abajo
        for (int fila = pivot+1  ; fila < m->getN() ; fila++) {

            //si el valor de la diagonal es cero paso a la siguiente columna
            if (! son_iguales(m->getVal(fila, fila-1), 0.0)) {

                // genero el valor que va a multiplicar la fila pivot (a_i_pivot / a_pivot_pivot)
                double valor_pivot = m->getVal(fila, pivot) / m->getVal(pivot, pivot) ;

                //(BORRAR LUEGO!!!)cout<<"valor pivot : getval("<< fila<<","<<pivot <<") = " << m->getVal(fila, pivot) << " / getval("<< pivot<<","<< pivot<<")" <<m->getVal(pivot,pivot) <<endl;

                b[fila] = b[fila] - b[pivot] * valor_pivot;
                // Teniendo el valor_pivot , resto toda las columnas de esa fila
                for (int columna = pivot ; columna < m->getN() ; columna++) {

                    //(BORRAR LUEGO!!!)cout << m->getVal(fila, columna) << " - " << m->getVal(pivot, columna) <<" * "<< valor_pivot <<" = "<< (m->getVal(pivot, columna) * valor_pivot) << " = "<< m->getVal(fila, columna) - (m->getVal(pivot, columna) * valor_pivot) <<endl;
                    // genero los valores de la matriz de gauss F_fila = F_fila - F_pivot * valor_pivot
                    double valor_fila_columna = m->getVal(fila, columna) - (m->getVal(pivot, columna) * valor_pivot);

                    // chequeo para descartar errores de representacion
                    if(son_iguales(valor_fila_columna, 0.0)){
                        valor_fila_columna=0.0;
                    }
                    m->setVal(fila,columna,valor_fila_columna);
                    //(BORRAR LUEGO!!!)cout << "----------------------------------------------"<<endl;

                }
            }
        }
    }
    // cout<< "a resolver gauss==============================================="<<endl;
    // resolver sistema Gr=b
    double* result = new double[m->getN()];

    for (int i = m->getN()-1 ; i >= 0 ; i--){
        //      cout <<"i= "<<i <<endl;
        double acum_suma=0.0;
        for(int j = m->getN()-1 ; j > i ; j-- ){
            //          cout <<"j= "<<j <<endl;

            acum_suma += m->getVal(i,j)*result[j] ;

        }

        // cout<< "b ["<<i<<"]= "<<b[i]<<endl;
        // cout<< "acum_suma= "<<acum_suma<<endl;
        // cout<< "m ["<<i<<","<<i<<"]= "<<m->getVal(i,i)<<endl;

        result [i] = (b[i] - acum_suma) /(double) m->getVal(i,i);

        // cout<< "result ["<<i<<"]= "<<result[i]<<endl;

    }
    // cout << "vector solucion" << endl;
    // for (int i=0 ; i<m->getM();i++){
    // cout << "    x" <<i<<"=" << result [i] <<endl;
    // }
    //    cout<< "a resolver gauss==============================================="<<endl;
    return result;
}

