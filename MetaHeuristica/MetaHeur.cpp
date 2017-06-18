#include <math.h>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;


struct Clique
{	
	bool vacia;
	int numeroVecinos;
	vector<int> vecinos;
	vector<int> miembros;
	void MostraClique(){
		cout << "Cantidad de vecinos: " << numeroVecinos << endl;
		for (int i = 0; i < miembros.size(); ++i)
		{
			if (miembros[i])
			{
				cout << i << " ";
			}
		}
		cout << endl;
	};
};

struct Graph
{
	int n,m;
	vector<vector<int> > matrizAdy;

	void InicializarMatriz(){
		matrizAdy.clear();
		for (int i = 0; i < n; ++i)
		{
			vector<int> tmp(n, 0);
			matrizAdy.push_back(tmp);
		}
	};

	void AgregarSiHaceClique(Clique cq, vector<int>& v)
	{
		if (cq.vacia){
			for (int i = 0; i < n; ++i)
			{
				v.push_back(i);
			}
			return;
		}

		for (int i = 0; i < n; ++i)
		{
			if(cq.miembros[i] == 0)
			{	
				bool haceClique = true;
				for (int j = 0; j < n; ++j)
				{
					if(cq.miembros[j] == 1 && matrizAdy[i][j] == 0) haceClique = false;
				}

				if (haceClique) v.push_back(i);
			}
		}
	};

	void AgregarVecinos(Clique& cq, int nodo){
		//agrega el nodo a miembros, lo saca de vecinos porque asumimos que solia ser un vecino, incrementamos el contador por cada 
		//vecino nuevo que antes no estaba
		if (cq.numeroVecinos != 0) cq.numeroVecinos--;	

		cq.miembros[nodo] = 1;
		for (int i = 0; i < n; ++i)
		{
			if (matrizAdy[nodo][i] == 1 && cq.miembros[i] == 0) {
				if (cq.vecinos[i] == 0){
					cq.numeroVecinos++;
				}
				cq.vecinos[i] = 1;
			}
		}
		cq.vecinos[nodo] = 0;
	};

	void ContarVecinos(Clique& cq, vector<int>& vecinos)
	{
		for (int i = 0; i < vecinos.size(); ++i)
		{
			if (cq.miembros[i] == 0)
			{
				int vec = 0;
				for (int j = 0; j < n; ++j)
				{
					if (cq.miembros[j] == 0 && cq.vecinos[j] == 0 && matrizAdy[i][j] == 1) vec++;
				}
				vecinos[i] = vec;
			}
			else
			{
				vecinos[i] = 0;
			}
		}
	}
};


void CalcularGrados(Graph g, vector<int>& v){
	for (int i = 0; i < g.n; ++i)
	{
		for (int j = 0; j < g.n; ++j)
		{
			if (g.matrizAdy[i][j]) v[i]++;
		}
	}
}

int DevolveMaxDeCandidatos(vector<int> vecinos, vector<int> candidatos){
	int max = 0;
	for (int i = 0; i < candidatos.size(); ++i)
	{
		if (max < vecinos[candidatos[i]]) max = vecinos[candidatos[i]];
	}
	return max;
}

int DevolveMinDeCandidatos(vector<int> vecinos, vector<int> candidatos){
	int min = 0x7FFFFFFF;
	for (int i = 0; i < candidatos.size(); ++i)
	{
		if (min > vecinos[candidatos[i]]) min = vecinos[candidatos[i]];
	}
	return min;
}

void MostrarMatriz(Graph g){
	for (int i = 0; i < g.n; ++i)
	{
		for (int j = 0; j < g.n; ++j)
		{
			cout << g.matrizAdy[i][j] << " ";
		}
		cout << endl;
	}
}

void CalcularCliqueMaxVecinos(Graph g, float alfa){
	srand(time(NULL));
	vector<int> vecinos(g.n,0);

	//Preprocesamiento

	CalcularGrados(g, vecinos);

	Clique clique;
	clique.vacia = true;
	clique.numeroVecinos = 0;
	clique.miembros= vector<int>(g.n, 0);
	clique.vecinos= vector<int>(g.n, 0);
	
	vector<int> listaReducidaCandidatos; //Hago una lista de candidatos posibles de los cuales comenzar con GRASP

	//Construccion

	vector<int> candidatos;
	g.AgregarSiHaceClique(clique, candidatos);
	
	while (candidatos.size() > 0)
	{	
		listaReducidaCandidatos.clear();
		int max = DevolveMaxDeCandidatos(vecinos, candidatos);
		int min = DevolveMinDeCandidatos(vecinos, candidatos);

		for (int i = 0; i < candidatos.size(); ++i)
		{
			if ( vecinos[candidatos[i]] > 0 && vecinos[candidatos[i]] >= max - alfa*(max - min)) 
				listaReducidaCandidatos.push_back(candidatos[i]);
		}
		if (listaReducidaCandidatos.size() == 0) break;

		int theChosenOne = rand() % listaReducidaCandidatos.size();
		
		clique.vacia = false;
		clique.miembros[listaReducidaCandidatos[theChosenOne]] = 1; //agrego el elegido a la clique
		g.AgregarVecinos(clique,listaReducidaCandidatos[theChosenOne]); //agrego sus vecinos que no estan ya en la clique al contador de la frontera
		
		g.ContarVecinos(clique, vecinos);
		
		candidatos.clear();
		
		g.AgregarSiHaceClique(clique, candidatos);

	}

	//Busqueda Local


}

int main(){
	Graph g;

	cin >> g.n; cin >> g.m;
	g.InicializarMatriz();
	for (int i = 0; i < g.m; ++i)
	{
		int o, d;
		cin >> o; cin >> d;
		g.matrizAdy[o][d] = 1;
		g.matrizAdy[d][o] = 1;
	}
	cout << "Envie parametro alfa" << endl;
	float alfa;
	cin >> alfa;
	
	CalcularCliqueMaxVecinos(g, alfa);

	return 0;
}