#ifndef FUERZA_BRUTA_H
#define FUERZA_BRUTA_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

struct GraphMat 			    // n-> Number of vertices, m-> Number of edges
{
    int n, m;
    vector<vector<int> > matrizAdy;		   // graph se representa con matriz de adyacencia
};

void createGraph(GraphMat* graph, int n, int m){

	graph->n = n;
	graph->m = m;

	vector<vector<int> > matriz(n, vector<int> (n, 0));

	graph->matrizAdy = matriz;
}

void addEdge(struct GraphMat* grafo, int src, int dest){
	grafo->matrizAdy[src][dest] = 1;
	grafo->matrizAdy[dest][src] = 1;
}

int gradoNodo(struct GraphMat* grafo, int nodo){
	int res = 0;
	for(int j = 0; j < grafo->n; j++){
		if(grafo->matrizAdy[nodo][j] == 1){
			res++;
		}
	}
	return res;
}

int cantUnosVec(vector<int>& vec){
	int res = 0;
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == 1){
			res++;
		}
	}
	return res;
}

int calcFrontera(struct GraphMat* grafo, vector<int> vec){
	int res = 0;
	int cantNodClique = cantUnosVec(vec);
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == 1){
			int aux = gradoNodo(grafo, i) - cantNodClique + 1;
			res = res + aux;
		}

	}
	return res;
}

bool esClique(struct GraphMat* grafo, vector<int>& vec){
	bool b = true;
	if(cantUnosVec(vec) == 0){
		return false;
	}
	for(int i = 0; i < vec.size() - 1; i++){
		if(vec[i] == 1){
			for(int j = i + 1; j < vec.size(); j++){
				if(vec[j] == 1){
					if(grafo->matrizAdy[i][j] != 1){
						b = false;
					}
				}
			}
		}
	}
	return b;
}

bool NoFormaClique(struct GraphMat* grafo, int nodo, vector<int>& vec){
	bool b = false;
	for(int i; i < vec.size(); i++){
		if(vec[i] == 1 && grafo->matrizAdy[i][nodo] == 0){
			b = true;
		}
	}
	return b;
}


// tiene una pequeña poda: NO va a la rama que corresponde a "usar el nodo" si no es adyacente al último usado (ya que no llevaría a una cliqué)
void cliqueMaxFrontAux(struct GraphMat* grafo, int n, int ite, vector<int>& vecAux, int &res, vector<int>& vecRes){
	if(ite == n){
		if(esClique(grafo, vecAux)){		// si es cliqué, entonces me fijo si tiene frontera mayor
			// mostrarVec(vecAux);
			int cant = calcFrontera(grafo, vecAux); 
			// cout << "La cant es: " << cant << endl;
			if(cant > res){
				res = cant;
				vecRes = vecAux;
			}
		}
	}
	if(ite < n){
		if(NoFormaClique(grafo, ite, vecAux)){		// si no forma clique con los anteriores, podá
			cliqueMaxFrontAux(grafo, n, ite + 1, vecAux, res, vecRes);	// caso recursivo no usar nodo
		}else{
			cliqueMaxFrontAux(grafo, n, ite + 1, vecAux, res, vecRes);	// caso recursivo no usar nodo
			vector<int> copia = vecAux;
			copia[ite] = 1;
			cliqueMaxFrontAux(grafo, n, ite + 1, copia, res, vecRes);	// caso recursivo usar nodo				}
		}
	}
}

// parece que esta podita ayudó bastante en los tiempos de cómputo.

// calcula la cliqué de maxima frontera
int cliqueMaxFront(struct GraphMat* grafo){
	int n = grafo->n;
	vector<int> vecRes(n);
	vector<int> vecAux(n);
	int res = 0;
	cliqueMaxFrontAux(grafo, n, 0, vecAux, res, vecRes);	// función auxiliar que hace todo
	// cout << "El resultado es " << res << endl;
	// cout << "Los nodos de la clique son: ";
	// mostrarUnosVec(vecRes);
	// int cantUn = cantUnosVec(vecRes);
	// cout << "Tiene " << cantUn << " nodos" << endl;
	// cout << endl;
	return res;
}

#endif