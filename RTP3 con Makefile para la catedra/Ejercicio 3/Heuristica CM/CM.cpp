#ifndef HEUR_H
#define HEUR_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility>
#include "Grafo.h"

using namespace std;

void ParaHeuristicaEmi(struct Graph* grafo, int &res, vector<int>& vecRes){
	
	//La idea es encontrar la clique maxima y devolver su frontera

	//en VecRes voy a guardar la clique mas grande guardada hasta el momento
	//en VecPasos voy a guardar las cliques formadas por cada iteracion

	//Como encontrar la clique maxima es un problema NP, vamos a implementar una heuristica para obtenerla.
	//Vamos a ordenar los nodos por grado de manera que d(NodosOrdenados[i]) >= d(NodosOrdenados[i+1])
	
	int cantNodosG = grafo->n;
	res = 0;	
	
	int NodosOrdenados[cantNodosG]; 
	for (int i = 0; i < cantNodosG; i++) //Inicializo el arreglo
	{
		NodosOrdenados[i] = i;
	}
	
	for (int i = 0; i < cantNodosG; i++) //Ordeno por grado
	{
		int posMaxParcial = i;
		for (int j = i; j < cantNodosG; j++)
		{
			if(gradoNodo(grafo, NodosOrdenados[j]) > gradoNodo(grafo, NodosOrdenados[posMaxParcial]))
			posMaxParcial = j;
		}
		int aux = NodosOrdenados[i];
		NodosOrdenados[i] = NodosOrdenados[posMaxParcial];
		NodosOrdenados[posMaxParcial] = aux;
	}


	int tamClique = 0;

	for (int i = 0; i < cantNodosG; i++) //	Paso 3  -  Paso 6
	{
	
		vector<int> vecPasos(grafo->n, 0); //creo nueva clique
		vecPasos[NodosOrdenados[i]] = 1;
		tamClique++;
		for (int j = 0; j < cantNodosG; j++) //Itero en orden de grado
		{

			if (i != j && nodoFormaClique(grafo, vecPasos, NodosOrdenados[j], tamClique) ) // Si no es el nodo inicial y forma clique lo agrego
			{
				vecPasos[NodosOrdenados[j]] = 1;
				tamClique++;
			}
		}


		int fronterasParcial = calcFrontera(grafo, vecPasos);
		if (res < fronterasParcial) //Si la clique creada es mas grande que la maxima guardada la reemplazo
		{
			vecRes = vecPasos;
			res = fronterasParcial;
		
		}		 
		tamClique = 0;
	}

}

pair< vector<int> , int> HeuristicaMCMF(Graph* grafo){		// total complej: O(n^3)
	int res = 0;
	vector<int> vecRes(grafo->n, 0);
	ParaHeuristicaEmi(grafo, res, vecRes);
	vector <int> clique ;
	int n = grafo-> n ;
	for(int i = 0 ; i < n; i ++){
		if(vecRes[i] == 1){
			clique.push_back(i);
		}
	}
	pair< vector<int> , int> resultado (clique, res);
	return resultado;
}


int main(){

	cout << "Ingrese los datos como indica el enunciado:" << endl;

	int n;
	cin >> n;

	int m;
	cin >> m;

	if (n > 0){
		Graph grafo;
		createGraph(&grafo, n, m);
		int c1, c2;

		for (int i = 0; i < m; i++)
		{
			cin >> c1; cin >> c2;
			addEdge(&grafo, c1-1, c2-1);
		}

		pair< vector<int> , int> res = HeuristicaMCMF(&grafo);



		cout << res.second << " " << res.first.size()  << " ";
		for (int i = 0; i < res.first.size(); i++)
		{
			cout << res.first[i] << " ";				
		}
		cout << endl;
		
	}
	
return 0;


}


#endif
