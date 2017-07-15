
#include <iostream>
#include <fstream>
#include "MetaHeur.cpp"

using namespace std;

Graph GenerarGrafoRandom(Graph g, int n)
{
	g.n = n;
	g.matrizAdy = vector<vector<int> >(g.n, vector<int>(g.n, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			g.matrizAdy[i][j] = rand() % 2;
			g.matrizAdy[j][i] = g.matrizAdy[i][j];
		}
	}
	return g;
}

void Mediciones(int sampleoGrafos)
{
	srand(time(NULL));

	fstream s("HeatMapGrasp.csv", ios::out);
	s << "cantNod,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200" << endl;
	for (int i = 20; i < 501; )
	{
		vector<int> resultados;
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}

		for (int j = 10; j < 201; )
		{
			resultados.push_back(0);
			for (int k = 0; k < sampleoGrafos; ++k)
			{
				Clique res = CalcularCliqueMaxVecinos(grafos[k], 0.5, j);
				resultados[(j-1)/10] += res.numeroVecinos;
			}
			cout << "Calcule para " << i << " nodos y " << j << " iteraciones " << endl;
			
			resultados[(j-1)/10] = resultados[(j-1)/10]/sampleoGrafos;
			j += 10;
		}
		float esperanza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			cout << (j+1)*10 << " " << resultados[j] << endl;;
			esperanza += resultados[j];
		}
		esperanza = esperanza/resultados.size();
		float varianza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			varianza += (resultados[j] - esperanza) * (resultados[j] - esperanza);
		}

		varianza = sqrt(varianza/resultados.size());
		s << i ;
		for (int j = 0; j < resultados.size(); ++j)
		{
			float res = 0;
			if (varianza != 0){
				res = (resultados[j] - esperanza)/varianza;	
			}
			s << ", " << res;
		}
		s << endl;

		i += 20;

	}
	

}

void MedicionesAlfa(int sampleoGrafos)
{
	srand(time(NULL));

	fstream s("HeatMapGraspAlfa.csv", ios::out);
	s << "cantNod,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00" << endl;
	for (int i = 20; i < 501; )
	{
		vector<int> resultados;
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}

		for (int j = 1; j < 21; j++ )
		{
			resultados.push_back(0);
			for (int k = 0; k < sampleoGrafos; ++k)
			{
				Clique res = CalcularCliqueMaxVecinos(grafos[k], (j*0.05), 150);
				resultados[(j-1)] += res.numeroVecinos;
			}
			cout << "Calcule para " << i << " nodos y " << j*0.05 << " = alfa " << endl;
			
			resultados[(j-1)] = resultados[(j-1)]/sampleoGrafos;
		}
		float esperanza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			esperanza += resultados[j];
		}
		esperanza = esperanza/resultados.size();
		float varianza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			varianza += (resultados[j] - esperanza) * (resultados[j] - esperanza);
		}

		varianza = sqrt(varianza/resultados.size());
		s << i ;
		for (int j = 0; j < resultados.size(); ++j)
		{
			float res = 0;
			if (varianza != 0){
				res = (resultados[j] - esperanza)/varianza;	
			}
			s << ", " << res;
		}
		s << endl;

		i += 20;

	}
	

}


void MedicionesIteraciones(int sampleoGrafos)
{
	srand(time(NULL));

	fstream s("HeatMapGraspIter.csv", ios::out);
	s << "IteracionesFijas,IteracionesReales,Tipo" << endl;
	for (int i = 500; i < 501; )
	{
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}

		for (int j = 10; j < 201; )
		{
			for (int k = 0; k < sampleoGrafos; ++k)
			{
				Clique res = CalcularCliqueMaxVecinos(grafos[k], 0.25, j);
				s << j << ", " << res.cantIteraciones << ", " << "Iteraciones Reales" << endl;
			}
			cout << "Calcule para " << i << " nodos y " << j << " iteraciones " << endl;
			
			j += 10;
		}
		

		i += 20;

	}
	

}


int main(){
	
	cout << "Arrancando Mediciones" << endl;
	//Mediciones(10);
	MedicionesAlfa(10);
	//MedicionesIteraciones(30);

	return 0;
}