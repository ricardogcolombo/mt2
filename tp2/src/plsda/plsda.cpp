#include "plsda.h"

void calcularPLSDA(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, 
					fstream &myfile, int cantidadIteraciones, int gamma){

    std::vector<vectorNum*> autovectores;
	//Matriz de Covarianza de X
    matrizNum *x = matrizDeCovarianza(etiquetados);
    //Matriz X traspuesta
    matrizNum *x_t = x->traspuesta();
    //Matriz de Y
    matrizNum *y;
    //Matriz de Y traspuesta
    matrizNum *y_t = y->traspuesta();

    myfile.precision(6);
    myfile << scientific;

    for (int i = 0; i < cantidadIteraciones; i++) {
    	matrizNum *m = x_t;
    	m->productoMatriz(y);
    	m->productoMatriz(y_t);
    	m->productoMatriz(x);
    	vectorNum * w_i = metodoDeLasPotencias(m);

        autovectores.push_back(w_i);

    	w_i->norma2();
    	vectorNum *t_i = x->producto(w_i);
    	matrizNum *x_temp = x;
    	matrizNum *y_temp = y;
    	x_temp -> producto(t_i); // traspuesto
    	x_temp -> producto(t_i); 
    	y_temp -> producto(t_i); // traspuesto
    	y_temp -> producto(t_i); 
    	x = x - x_temp
    	y = y - y_temp
    }

}
