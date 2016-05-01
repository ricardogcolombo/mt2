//Include all our files here
#include "instancia/instancia.h"
#include "matriz/matriz.h"

//standard
/* #include <algorithm>    // std::sort */
// #include <cmath>
// #include <climits>
#include <vector>       // std::vector
#include <iostream>
// #include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/time.h>

using namespace std;

int **kfolds(string archivo, int &cantidadDePruebas, int &alfa,int&gamma, int &vecinos);
void prepararNuevaEntrada(vector<imagen> entradaOriginal, vector<imagen> &entradaNueva, vector<imagen> &testeo, int *kfold) ;
void ejecutar(int metodo, vector<imagen> &entradas, vector<imagen> &test, int alfa, int gamma, int vecinos, fstream& myfile) ;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Error en la cantidad de argumentos!!" << endl;
        return -1;
    }

    string archivoDeEntrada (argv[1]);
    string archivoDeSalida (argv[2]);
    string metodo;

    if (argc == 3) {
        metodo = "1";
    } else {
        metodo = argv[3];
    }

    int cantidadDePruebas,alfa,gamma,vecinos;

    // creo una matriz para el cross validation
    cout << "Iniciando Kfolds...." << endl;
    int **kfold = kfolds(archivoDeEntrada, cantidadDePruebas, alfa, gamma, vecinos);

    cout << "Cantidad De Pruebas: " << cantidadDePruebas << endl;
    cout << "Vecinos para el KNN: " << vecinos << endl;
    if (atoi(metodo.c_str()) == 1) {
        cout << "Alfa Para PCA: " << alfa << endl;
        cout << "Iteraciones Para PLSDA: " << gamma<< endl;
    }

    fstream myfile(archivoDeSalida.c_str(), ios::out | ios::trunc);

    for (int i = 0; i < cantidadDePruebas; i++) {
        cout << "Cargando Base de datos..." << endl;
        //TODO : mover esto afuera del for y usar el operator=
        vector<imagen> entradas = procesarEntrada("train.csv", false);

        vector<imagen> testeo;
        vector<imagen> entrenamiento;

        cout << "Corriendo test: " << i + 1 << endl;
        // TODO: Mover afuera del for y usar operator =
        prepararNuevaEntrada(entradas, entrenamiento, testeo, kfold[i]);
        ejecutar(atoi(metodo.c_str()), entrenamiento, testeo, alfa,gamma, vecinos, myfile);

        //Elimino todos los vectores creados
        entradas.erase(entradas.begin(), entradas.end());
        for (int i = 0; i < entrenamiento.size(); i++) {
            delete entrenamiento[i].vect;
        }
        entrenamiento.erase(entrenamiento.begin(), entrenamiento.end());
        for (int i = 0; i < testeo.size(); i++) {
            delete testeo[i].vect;
        }
        testeo.erase(testeo.begin(), testeo.end());
    }
    myfile.close();
    //Esto es para hacer el K folds
    cerr << endl;
    cout << "Fin!" << endl;
    return 0;
}

int **kfolds(string archivo, int &cantidadDePruebas, int &alfa,int&gamma, int &vecinos) {
    int **kfold;
    string hola;
    fstream myfile(archivo.c_str(), ios_base::in);
    // leo los parametros de entrada
    //url del archivo
    myfile >> hola;
    // k vecinos
    myfile >> vecinos;
    // alfa para pca
    myfile >> alfa;
    // gamma para plsda
    myfile >> gamma;
    // K cantidad de elementos
    myfile >> cantidadDePruebas;

    kfold = new int*[cantidadDePruebas];
    for (int i = 0; i < cantidadDePruebas; i++) {
        kfold[i] = new int[42000];
        for (int j = 0; j < 42000; j++) {
            myfile >> kfold[i][j];
        }
    }
    myfile.close();
    return kfold;
}

void prepararNuevaEntrada(vector<imagen> entradaOriginal, vector<imagen> &entradaNueva, vector<imagen> &testeo, int *kfold) {
    int cantidadDeTests = 0;
    for (int i = 0; i < 42000; i++) {
        if (kfold[i] == 1) {
            entradaNueva.push_back(entradaOriginal[i]);
        } else {
            cantidadDeTests++;
            testeo.push_back(entradaOriginal[i]);
        }
    }
    cout << "Cantidad De imagenes a reconocer: " << cantidadDeTests << endl;
}

void ejecutar(int metodo, vector<imagen> &entradas, vector<imagen> &test, int alfa, int gamma, int vecinos, fstream& myfile) {
    //knn

    /*tiempos*/
    timeval start, end;
    if (metodo == 0) {
        cout << "Ejecutando metodo KNN..." << endl;
        gettimeofday(&start, NULL);
        // calcularknn(entradas, test, vecinos);
    }
    //pca + knn
    if (metodo == 1) {
        cout << "Ejecutando metodo PCA..." << endl;
        // calcularPca(entradas, test, myfile, alfa);
        cout << "Ejecutando KNN sobre el PCA..." << endl;
        gettimeofday(&start, NULL);
        // calcularknn(entradas, test, vecinos);
    }
    // plsda + knn
    if(metodo ==2 ){
        cout << "Ejecutando metodo PCA..." << endl;
        // calcularPLSDA(entradas, test, myfile, gamma);
        cout << "Ejecutando KNN sobre el PCA..." << endl;
        gettimeofday(&start, NULL);
        // calcularknn(entradas, test, vecinos);
    }

    long elapsed_seconds; /* diff between seconds counter */
    long elapsed_useconds; /* diff between microseconds counter */
    /*tiempos*/
    gettimeofday(&end, NULL);
    elapsed_seconds = end.tv_sec - start.tv_sec;
    double time=  ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5;
    cerr << time<< " ";
}
