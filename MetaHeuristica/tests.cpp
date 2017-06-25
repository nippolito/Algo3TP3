
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
	s << "cantNod,iter,res" << endl;
	for (int i = 5; i < 500; )
	{
		vector<float> resultados;
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}

		for (int j = 1; j < 202; )
		{
			resultados.push_back(0);
			for (int k = 0; k < sampleoGrafos; ++k)
			{
				Clique res = CalcularCliqueMaxVecinos(grafos[k], 0.5, j);
				resultados[j/10] += (float)res.numeroVecinos;
			}
			resultados[j/10] = resultados[j/10]/sampleoGrafos;
			j += 10;
		}
		cout << endl;
		float esperanza;
		for (int j = 0; j < 20; ++j)
		{
			esperanza += resultados[j];
		}
		esperanza = esperanza/resultados.size();

		float varianza;
		for (int j = 0; j < 20; ++j)
		{
			varianza += (resultados[j] - esperanza) * (resultados[j] - esperanza);
		}
		varianza = sqrt(varianza/resultados.size());
		
		cout << "Resultados para " << i << " nodos " << endl;
		for (int j = 0; j < resultados.size(); ++j)
		{
			resultados[j] = (resultados[j] - esperanza)/varianza;
			cout << resultados[j] << " ";
			s << i << ", " << j*20 + 1 << ", " << resultados[j] << endl;
		}
		cout << endl;

		i += 20;

	}
	

}

int main(){
	
	cout << "Arrancando Mediciones" << endl;
	Mediciones(10);

	return 0;
}