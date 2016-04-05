#include "eliminaciongauss/elimgauss.h"
#include "matriz/matriz.h"
#include "instancia/instancia.h"
#include "wp/wp.h"
#include "cholesky/cholesky.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/time.h>

using namespace std;

instancia * generarInstanciaDesdeArchivo(ifstream &archivoDeEntrada);
instancia * generarInstanciaVacia(ifstream &archivoDeEntrada);
void printVector(double * ,int );

//El programa requiere 3 parametros, un archivo de entrada, uno de salida y el modo a ejecutar.
int main(int argc, char *argv[]) {
    timeval startGauss, endGauss;
    timeval startCholesky, endCholesky;
    timeval startWP, endWP;
    long elapsed_mtime; /* elapsed time in milliseconds */
    long elapsed_seconds; /* diff between seconds counter */
    long elapsed_useconds; /* diff between microseconds counter */



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
    ofstream archivoTiempos;
    archivoDeSalida.setf(ios::fixed, ios::floatfield); // tipo salida
    archivoTiempos.setf(ios::fixed, ios::floatfield); // tipo salida
    archivoTiempos.precision(6); // cant decimales
    archivoDeSalida.precision(6); // cant decimales
    archivoDeSalida.open(argv[2]);


    // genero una instancia Matriz de resultados Ganadores y vector de totales
    instancia *ins= generarInstanciaDesdeArchivo(archivoDeEntrada);

    // base para el resultado
    double* respuesta = new double[ins->getTotalEquipos()];
    for (i = 0; i < ins->getTotalEquipos(); ++i) {
        respuesta[i] = 0.0;
    }

    Matriz * CMM = ins->getCMM();
    string totales =  to_string(ins->getTotalEquipos()) + " " + to_string(ins->getTotalPartidos()) + " ";

    // metodo Metodo CMM Con Gauss
    if (strcmp(argv[3], "0") == 0) {
        cout << "Corriendo Metodo Gauss..." << endl;

		double timeGauss= 0.0;
		for (int iteraciones = 0; iteraciones<5; iteraciones++){
	        gettimeofday(&startGauss, NULL);
	        
	        respuesta =gauss(CMM,ins->getVectorB());
	        
	        gettimeofday(&endGauss, NULL);

	        elapsed_seconds = endGauss.tv_sec - startGauss.tv_sec;
	        elapsed_useconds = endGauss.tv_usec - startGauss.tv_usec;
        	
			//if (((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5 < timeGauss){
			timeGauss+= ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
			//}  
		}
		timeGauss= timeGauss/5;

        archivoTiempos.open("tiempos/tiempos0.txt", std::ofstream::out | std::ofstream::app);
        archivoTiempos << ins->getTotalEquipos() << " "  << ins->getTotalPartidos() << " " <<timeGauss<< endl;
        archivoTiempos.close();
    }
    // metodo Metodo CMM Con CHOLESKY
    if (strcmp(argv[3], "1") == 0  ||strcmp(argv[3], "3") == 0 ) {
        cout << "Corriendo Metodo Cholesky..." << endl;
        gettimeofday(&startCholesky, NULL);

        //LLAMO CHOLESKy
        respuesta = cholesky(CMM,ins->getVectorB());

        gettimeofday(&endCholesky, NULL);
        elapsed_seconds = endCholesky.tv_sec - startCholesky.tv_sec;
        elapsed_useconds = endCholesky.tv_usec - startCholesky.tv_usec;
        // aca se guarda el tiempo
        double timeCholesky =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;

        archivoTiempos.open("tiempos/tiempos1.txt", std::ofstream::out | std::ofstream::app);
        archivoTiempos <<  ins->getTotalEquipos() << " "  << ins->getTotalPartidos() << " " <<timeCholesky<< endl;
        archivoTiempos.close();
    }

    // metodo WP
    if (strcmp(argv[3], "2") == 0) {
        cout << "Corriendo Metodo WP..." << endl;

        gettimeofday(&startWP, NULL);
        respuesta = wp(ins);
        gettimeofday(&endWP, NULL);
        elapsed_seconds = endWP.tv_sec - startWP.tv_sec;
        elapsed_useconds = endWP.tv_usec - startWP.tv_usec;
        double timeWP =  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
        archivoTiempos.open("tiempos/tiempos2.txt", std::ofstream::out | std::ofstream::app);
        archivoTiempos <<ins->getTotalEquipos() << " "  << ins->getTotalPartidos() << " " << timeWP<< endl;
        archivoTiempos.close();

    }

    if (strcmp(argv[3], "3") == 0) {

        ofstream archivoModificadoCHOLESKY;

        // aca se escupe el ranking // base para el resultado
        double* respuestaModificada = new double[ins->getTotalEquipos()];
        for (i = 0; i < ins->getTotalEquipos(); ++i) {
            respuestaModificada[i] = 0.0;
        }

        cout << "Corriendo Metodo CHOLESKY RANDOM 1000 partidos..." << endl;
        // aa se modifican los partidos ganados
        for (i = 0; i < 100; ++i) {
            // agarro uno random
            int e1 = rand() % ins->getTotalEquipos();
            // le hago ganar un perder contra uno que haya ganado
            ins->ganaPartido(e1);
        }
        // genero el nuevo B
        ins->generarVectorB();

        //LLAMO CHOLESKy
        respuestaModificada = cholesky(CMM,ins->getVectorB());

        // Aca saco los tiempos al archivo tiempos4
        archivoModificadoCHOLESKY.open("tests/resultadosCholeskyModificado.out", std::ofstream::out | std::ofstream::app);
        // archivoTiempos <<totales<< timeWP<< endl;
        // archivoTiempos.close();

        for (int w = 0; w < ins->getTotalEquipos(); w++) {
            archivoModificadoCHOLESKY<< respuestaModificada[w] << endl;
        }
        archivoModificadoCHOLESKY.close();
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

// generar instancia
// instancia *generarInstanciaVacia(ifstream &archivoDeEntrada){
// int n,k,i,fecha;
// int equipo1,equipo2,goles1,goles2;

// //leo cantidad de equipos
// archivoDeEntrada >> n;
// //leo cantidad de partidos
// archivoDeEntrada >> k;
// // creo la tabla de resultados ganadores
// Matriz * tablaResultados  =  new Matriz(n,n);
// // creo la tabla de partidos totales
// int* totales = new int[n];
// for (i = 0; i < n; ++i) {
// totales[i]=0;
// }

// instancia *res =new instancia();
// res->setTotalPartidos(k);
// res->setGanados(tablaResultados);
// res->setTotales(totales);
// res->generarCMM();
// res->generarVectorB();
// return res;
// };

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
    res->setTotalPartidos(k);
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
