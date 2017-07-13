#ifndef HEUR_H
#define HEUR_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility>
#include "Grafo.h"

using namespace std;



void ParaHeuristica(struct Graph* grafo, int &res, vector<int>& nodosMejorClique){
	
	int nodoGM = nodoGradoMaximo(grafo);		// arranco por un nodo de grado máximo
	int mejorFront = gradoNodo(grafo, nodoGM);
	int ultNodoAg = nodoGM;
	vector<vector <int> > listA = grafo->listaAdy;
	int cantNodosClique = 1;
	int posFrontMejor = -1;

	vector<int> cliqueEnVecBool(grafo->n, 0);
	cliqueEnVecBool[nodoGM] = 1;

	nodosMejorClique.push_back(nodoGM);

	vector<int> nodosCliquePos = nodosMejorClique;

	// hasta acá O(n^2)

	int ultNodoAux = ultNodoAg;

	for(int i = 0; i < listA[ultNodoAg].size(); i++){
		int aux = mejorFront + gradoNodo(grafo, listA[ultNodoAg][i]) - (cantNodosClique + 1);
		if(aux > posFrontMejor){
			posFrontMejor = aux;
			ultNodoAux = listA[ultNodoAg][i];
		}
	}

	ultNodoAg = ultNodoAux;

	cliqueEnVecBool[ultNodoAg] = 1;
	nodosCliquePos.push_back(ultNodoAg);
	cantNodosClique++;

	// luego de esto en nodosCliquePos me queda el que daba la mejor frontera de 2 nodos que contenía al
	// nodo de grado máximo y en ultNodoAg el último nodo que agregué. 

	if(posFrontMejor > mejorFront){
		mejorFront = posFrontMejor;
		nodosMejorClique = nodosCliquePos;
	}

	// acá actualicé la mejor frontera junto a sus nodos.

	ultNodoAux = ultNodoAg;
	bool b = true;
	int mejorFrontUnNodoMenos = posFrontMejor;

	// ciclo que analiza hasta que no haya más cliques, siempre agregando al nodo que forma la cliqué de mayor frontera con
	// los que estaban antes
	while(b){
		b = false;
		posFrontMejor = -1;
		for(int i = 0; i < listA[ultNodoAg].size(); i++){
			if(noEstabaEnClique(grafo, cliqueEnVecBool, listA[ultNodoAg][i]) && nodoFormaClique(grafo, cliqueEnVecBool, listA[ultNodoAg][i], cantNodosClique)){
				b = true;
				int frontAux = mejorFrontUnNodoMenos + gradoNodo(grafo, listA[ultNodoAg][i]) - (cantNodosClique * 2);
				if(frontAux > posFrontMejor){
					posFrontMejor = frontAux;
					ultNodoAux = listA[ultNodoAg][i];
				}
			}
		}

		ultNodoAg = ultNodoAux;

		if(b){
			nodosCliquePos.push_back(ultNodoAg);
			cliqueEnVecBool[ultNodoAg] = 1;
			cantNodosClique++;
		}

		if(posFrontMejor > mejorFront){
			mejorFront = posFrontMejor;
			nodosMejorClique = nodosCliquePos;
		}

		mejorFrontUnNodoMenos = posFrontMejor;
		
	}

	res = mejorFront;

	// 
}

pair< vector<int> , int> HeuristicaNipo(Graph* grafo){		// total complej: O(n^4)
	int res = 0;
	vector<int> nodosMejorClique(0, 0);

	ParaHeuristica(grafo, res, nodosMejorClique);

	pair< vector<int> , int> resultado (nodosMejorClique, res);

	// mostrarVector(nodosMejorClique);

	// cout << "El resultado es " << res << endl;
	// cout << "Los nodos de la clique son: ";
	// mostrarUnosVec(vecRes);
	// int cantUn = cantUnosVec(vecRes);
	// cout << "Tiene " << cantUn << " nodos" << endl;
	// cout << endl;
	return resultado;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//HEURISTICA EMI
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




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

pair< vector<int> , int> HeuristicaEmi(Graph* grafo){		// total complej: O(n^3)
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
	// cout << "El resultado es " << res << endl;
	// cout << "Los nodos de la clique son: ";
	// mostrarUnosVec(vecRes);
	// int cantUn = cantUnosVec(vecRes);
	// cout << "Tiene " << cantUn << " nodos" << endl;
	// cout << endl;
	return resultado;
}


#endif
