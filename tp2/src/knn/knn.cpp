#include "knn.h"

int calcularknn(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, int cantidadDeVecinosMasCercanos) {
    fstream myfile("Resultados.csv",ios::out | ios::app);
    fstream experimentos("experimentos.txt",ios::out | ios::app);
    experimentos.precision(3);

    experimentos<< "cantidad de vecinos mas cercanos" << cantidadDeVecinosMasCercanos <<endl;
    int lepegue = 0;
    vector<double> falsosPositivos (10,0);
    vector<double> falsosNegativos(10,0);
    vector<double> positivos (10,0);
    vector<double> presicion(10,0);
    vector<double> recall(10,0);
    int *etiqueta = new int[sinEtiquetar.size()];

    myfile << "ImageId,Label" << endl;
    for(int i = 0; i < sinEtiquetar.size(); i++) {
        etiqueta[i] = encontrarEtiqueta(etiquetados, sinEtiquetar[i], cantidadDeVecinosMasCercanos);
        myfile << i+1 << "," << etiqueta[i] << endl;
        if(etiqueta[i] == sinEtiquetar[i].label){
            lepegue++;
            positivos[sinEtiquetar[i].label]+=1;
        }else{
            falsosPositivos[etiqueta[i]]+=1;
            falsosNegativos[sinEtiquetar[i].label]+=1;
        }
    }
    experimentos<< "presicion" <<endl;
    for(int i = 0;i<10;i++){
        presicion[i] = positivos[i]/double (falsosPositivos[i]+positivos[i]);
        experimentos<< presicion[i] << ",";
    }

    experimentos<< endl;
    experimentos<< "Recall" <<endl;
    for(int i = 0;i<10;i++){
        recall[i] = positivos[i]/double (falsosNegativos[i]+positivos[i]);
        experimentos<< recall[i]/double (recall[i]+presicion[i]) << ",";
    }
    experimentos<< endl;

    experimentos<< "F1 Score" <<endl;
    for(int i = 0;i<10;i++){
        experimentos<< recall[i]/double (recall[i]+presicion[i]) << ",";
    }
    experimentos<< endl;
    myfile.close();
    experimentos.close();
    // cout << "Cantidad De Aciertos " << lepegue << endl;
    return lepegue;
}

class mycomparison
{
    bool reverse;
    public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (resultado lhs,resultado rhs) const
    {
        //comprobar que es asi y no con el signo al reves
        return lhs.norma > rhs.norma;
    }
};


int encontrarEtiqueta(vector<entrada> &etiquetados, entrada &instancia,int cantidadDeVecinosMasCercanos){

    priority_queue<resultado, vector<resultado>,mycomparison> resultados;

    for(int i= 0; i < etiquetados.size(); i++)
    {
        vectorNum* restaVectores = etiquetados[i].vect->resta(instancia.vect);
        resultado result;
        result.norma  = restaVectores->norma2();
        delete restaVectores;
        result.clase = etiquetados[i].label;
        resultados.push(result);
    }

    int numeros[10];
    for(int i = 0; i < 10; i++)
        numeros[i] = 0;

    for(int i = 0; i < cantidadDeVecinosMasCercanos; i++)
    {
        resultado result = resultados.top();
        numeros[result.clase]++;
        resultados.pop();
    }

    int max = 0;
    int claseMax = -1;
    for(int i = 0; i < 10; i++)
    {
        if(max < numeros[i])
        {
            max = numeros[i];
            claseMax = i;
        }
    }
    if(claseMax == -1)
        cout << "Error determinando clase" << endl;
    return claseMax;
}

