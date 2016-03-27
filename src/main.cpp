#include "EliminacionGauss/ElimGauss.h"
#include "Matriz/Matriz.h"
#include "Instancia/instancia.h"
#include "WP/WP.h"
#include "cholesky/cholesky.h"
#include "EliminacionGauss/ElimGauss.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/time.h>
using namespace std;

instancia * generarInstanciaDesdeArchivo(ifstream &archivoDeEntrada);
void printVector(double * ,int );

//El programa requiere 3 parametros, un archivo de entrada, uno de salida y el modo a ejecutar.
int main(int argc, char *argv[]) {
    int i;
    // argumentos
    // 0 - main
    // 1 archivo entrada
    // 2 archivo salida
    // 3 modo
    if (argc != 4) {
        cout << "Error, Faltan Argumentos" << endl;
        return 1;
    }

    //leo archivo entrada
    ifstream archivoDeEntrada (argv[1]);

    //preparo archivo salida para escritura
    ofstream archivoDeSalida;
    archivoDeSalida.setf(ios::fixed, ios::floatfield); // tipo salida
    archivoDeSalida.precision(6); // cant decimales
    archivoDeSalida.open(argv[2]);


    // genero una instancia Matriz de resultados Ganadores y vector de totales
    instancia *ins= generarInstanciaDesdeArchivo(archivoDeEntrada);

    // base para el resultado
    double* respuesta = new double[ins->getTotalEquipos()];
    for (i = 0; i < ins->getTotalEquipos(); ++i) {
        respuesta[i] = 0.0;
    }

    // metodo WP
    if (strcmp(argv[3], "0") == 0) {
        cout << "Corriendo Metodo WP..." << endl;

        respuesta = wp(ins);
    }

    Matriz * CMM = ins->getCMM();

    // metodo Metodo CMM Con Gauss
    if (strcmp(argv[3], "1") == 0) {
        cout << "Corriendo Metodo Gauss..." << endl;

        respuesta =gauss(CMM,ins->getVectorB());

    }
    ins->print();
    // metodo Metodo CMM Con CHOLESKY
    if (strcmp(argv[3], "2") == 0) {
        cout << "Corriendo Metodo Cholesky..." << endl;
        /*int n = CMM->getN();
          double input [n*n];

        //double *L = (double*)calloc(n * n, sizeof(double));
        for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
        input[i*n+j]= CMM->getVal(i, j);
        }
        }

        respuesta =  cholesky(input, n);
        */
        respuesta = cholesky2(CMM,ins->getVectorB());
        printVector(respuesta,CMM->getN());
        /*

           for (int i = 0; i < n; i++)
           for (int j = 0; j < (i+1); j++) {
           double s = 0;
           for (int k = 0; k < j; k++)
           s += L[i * n + k] * L[j * n + k];
           L[i * n + j] = (i == j) ?
           sqrt(A[i * n + i] - s) :
           (1.0 / L[j * n + j] * (A[i * n + j] - s));
           }


           for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++)
           printf("%2.5f ", L[i * n + j]);
    //   printf("%2.5f ", CMM->getVal(i ,j));
    printf("\n");
    }

*/

        // respuesta = wp(in);
    }

    //para imprimir una instancia (Matriz resultados, Vector totales y matriz CMM)
    // ins->print();

    for (int w = 0; w < ins->getTotalEquipos(); w++) {
        archivoDeSalida << respuesta[w] << endl;
    }

    archivoDeSalida.close();
    archivoDeEntrada.close();
    return 0;
}

instancia *generarInstanciaDesdeArchivo(ifstream &archivoDeEntrada){
    int n,k,i,fecha;
    int equipo1,equipo2,goles1,goles2;


    //leo cantidad de equipos
    archivoDeEntrada >> n;
    //leo cantidad de partidos
    archivoDeEntrada >> k;
    // creo la tabla de resultados ganadores
    Matriz * tablaResultados  =  new Matriz(n,n);
    // creo la tabla de partidos totales
    int* totales = new int[n];
    for (i = 0; i < n; ++i) {
        totales[i]=0;
    }

    if (archivoDeEntrada.is_open())
    {
        for (i = 0; i < k; ++i) {
            //primer linea es fecha
            archivoDeEntrada >> fecha;
            // segunda linea es el numero del primer equipo
            archivoDeEntrada >> equipo1;
            // tercer linea es la cantidad de goles del primer equipo
            archivoDeEntrada >> goles1;
            // cuarta linea es el numero del segundo equipo
            archivoDeEntrada >> equipo2;
            // quinta linea es la cantidad de goles del segundo equipo
            archivoDeEntrada >> goles2;

            totales[equipo1-1]++;
            totales[equipo2-1]++;

            if(goles1>goles2){
                int actual = tablaResultados->getVal(equipo1-1,equipo2-1);

                tablaResultados->setVal(equipo1-1,equipo2-1,actual+1);

            }else{
                int actual = tablaResultados->getVal(equipo2-1,equipo1-1);

                tablaResultados->setVal(equipo2-1,equipo1-1,actual+1);
            }
        }
        archivoDeEntrada.close();
    }
    instancia *res =new instancia();
    res->setGanados(tablaResultados);
    res->setTotales(totales);
    res->generarCMM();
    res->generarVectorB();
    return res;
}

void printVector(double * vec,int longitud){
    int i;
    for (i = 0; i < longitud; ++i) {
        cout << vec[i]<< endl;
    }

}
