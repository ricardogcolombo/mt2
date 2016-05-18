#include "knn.h"

void calcularknn(vector<entrada> &etiquetados, vector<entrada> &sinEtiquetar, int cantidadDeVecinosMasCercanos)
{
	fstream myfile("Resultados.csv",ios::out | ios::app);
	int lepegue = 0;
	int *etiqueta = new int[sinEtiquetar.size()];
	int ArraydeAciertos [10] = {0,0,0,0,0,0,0,0,0,0};
	int ArraydePifies 	[10] = {0,0,0,0,0,0,0,0,0,0};

	int j = 0 ;
	myfile << "ImageId,Label" << endl;
	for(int i = 0; i < sinEtiquetar.size(); i++)
	{
		//El .label no lo genero , asi que supongo que es la posta
		etiqueta[i] = encontrarEtiqueta(etiquetados, sinEtiquetar[i], cantidadDeVecinosMasCercanos);
		myfile << i+1 << "," << etiqueta[i] << endl;
		if(etiqueta[i] == sinEtiquetar[i].label)
			{	j = sinEtiquetar[i].label;
				ArraydeAciertos[j]+=1;
				lepegue++;
			}
		else
		{	
			j = sinEtiquetar[i].label;
			ArraydePifies[j]+=1;
		}
	}
	myfile.close();
	cout << "Cantidad De Aciertos " << lepegue << endl;
	cerr << lepegue << " ";
	//Imprimo Arrays
	cout << "\n" ;
	cout << "Array de Aciertos" << endl;
	for (int i = 0; i < 10; ++i)
	{
		cout<< "Aciertos de " << i << " son " << ArraydeAciertos[i] << endl;
	}
	cout << "\n" << endl;
	cout << "Arrays de Fracasos" << endl;
		for (int i = 0; i < 10; ++i)
		{
			cout<< "Fracasos de " << i << " son " << ArraydePifies[i] << endl;
		}	


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

