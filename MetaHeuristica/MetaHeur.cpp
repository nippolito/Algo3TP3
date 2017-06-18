#include <math.h>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include "BusquedaLocal.h"

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

Clique CalcularCliqueMaxVecinos(Graph g, float alfa, int ciclosGrasp){
	srand(time(NULL));
	//estructuras para el busqueda local de grego
	set<int> matrix[g.n];
	for (int i = 0; i < g.n; ++i)
	{
		for (int j = 0; j < g.n; ++j)
		{
			if (g.matrizAdy[i][j]){
				matrix[j].insert(i);
				matrix[i].insert(j);
			}
		}
	}
	
	Clique solucionActual;
	solucionActual.numeroVecinos = 0;
	solucionActual.miembros= vector<int>(g.n, 0);

	for (int ciclo = 0; ciclo < ciclosGrasp; ++ciclo)
	{
		
		//Preprocesamiento
		vector<int> vecinos(g.n,0);
		CalcularGrados(g, vecinos);

		Clique clique;
		clique.vacia = true;
		clique.numeroVecinos = 0;
		clique.miembros= vector<int>(g.n, 0);
		clique.vecinos= vector<int>(g.n, 0); 
		
		vector<int> listaReducidaCandidatos; //Hago una lista de candidatos posibles de los cuales comenzar con GRASP

		//Construccion

		vector<int> candidatos;
		g.AgregarSiHaceClique(clique, candidatos); //como la clique esta vacia, candidatos = V
		
		while (candidatos.size() > 0) //hayan candidatos para agregar a la clique
		{	
			listaReducidaCandidatos.clear();
			int max = DevolveMaxDeCandidatos(vecinos, candidatos);
			int min = DevolveMinDeCandidatos(vecinos, candidatos);

			for (int i = 0; i < candidatos.size(); ++i)
			{
				if ( vecinos[candidatos[i]] > 0 && vecinos[candidatos[i]] >= max - alfa*(max - min)) //si aportan mas de un vecino y estan en rango
					listaReducidaCandidatos.push_back(candidatos[i]);
			}
			if (listaReducidaCandidatos.size() == 0) break; //si no hay candidatos que aumenten el resultado actual

			int theChosenOne = rand() % listaReducidaCandidatos.size(); //random del GRASP 
			
			clique.vacia = false;
			clique.miembros[listaReducidaCandidatos[theChosenOne]] = 1; //agrego el elegido a la clique
			g.AgregarVecinos(clique,listaReducidaCandidatos[theChosenOne]); //agrego sus vecinos que no estan ya en la clique al contador de la frontera
			
			g.ContarVecinos(clique, vecinos); //actualiza el vector de vecinos diciendo cuanto aporta cada uno si lo agregase a la clique
			
			candidatos.clear(); //borro el vector de candidatos
			
			g.AgregarSiHaceClique(clique, candidatos); //lo lleno con todos los vertices que pueden agrandar la clique

		}


		//Busqueda Local
		set<int> solAct;
		for (int i = 0; i < g.n; ++i)
		{
			if (clique.miembros[i]) solAct.insert(i);
		}

		int numeroFrontera = BusquedaLocal(matrix, solAct, g.n, 0);
		
		//Comparacion con solucion actual
		if (numeroFrontera > solucionActual.numeroVecinos){
			solucionActual.numeroVecinos = numeroFrontera;
			for (int i = 0; i < g.n; ++i)
			{
				if(solAct.find(i) == solAct.end()){
					solucionActual.miembros[i] = 0;
				}
				else{
					solucionActual.miembros[i] = 1;
				}
			}
		}
		
	}

	return solucionActual;

}

int main(){
	Graph g;

	cin >> g.n; cin >> g.m;
	g.matrizAdy = vector<vector<int> >(g.n, vector<int>(g.n, 0));
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
	
	Clique res = CalcularCliqueMaxVecinos(g, alfa, 5);

	res.MostraClique();

	return 0;
}

