#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility>

using namespace std;


struct Graph 			    // n-> Number of vertices, m-> Number of edges
{
    int n, m;
    vector<vector<int> > listaAdy;		   // graph se representa con lista de adyacencia
};

void createGraph(Graph* graph, int n, int m){

	graph->n = n;
	graph->m = m;

	vector<vector<int> > lista(n, vector<int> (0, 0));

	graph->listaAdy = lista;
}

void addEdge(struct Graph* grafo, int src, int dest){
	grafo->listaAdy[src].push_back(dest);
	grafo->listaAdy[dest].push_back(src);
}

void mostrarVector(vector<int>& vec){
	// cout << "longitud de vec: " << vec.size() << endl;

	if(vec.size() == 1){
		cout << "[" << vec[0] << "]" << endl;
	}else{
		cout << "[" << vec[0] << ",";	
	}
	for(int i = 1; i < vec.size(); i++){
		if(i < vec.size() - 1){
			cout << vec[i] << ",";
		}else{
			cout << vec[i] << "]" << endl;
		}
	}
}



int gradoNodo(struct Graph* grafo, int nodo){
	return grafo->listaAdy[nodo].size();
}

int nodoGradoMaximo(struct Graph* grafo){
	int res = 0;
	int gradRes = gradoNodo(grafo, 0);
	int n = grafo->n;
	for(int i = 1; i < n; i++){
		int aux = gradoNodo(grafo, i);
		if(aux > gradRes){
			res = i;
			gradRes = aux;
		}
	}
	return res;
}

bool esVecino(struct Graph* grafo, int nodo1, int nodo2){
	int z1,z2, n;
	
	if(grafo->listaAdy[nodo1].size() > grafo->listaAdy[nodo2].size()){
		z1 = nodo2; 
		z2 = nodo1;
		n = grafo->listaAdy[nodo2].size();
	}
	else{
		z1 = nodo1;
		z2 = nodo2;
		n = grafo->listaAdy[nodo1].size();
	}
	
	
	bool res = false;
	for(int i = 0; i < n; i++){
		if(grafo->listaAdy[z1][i] == z2){
			res = true;
		}
	}
	return res;
}

bool nodoFormaClique(struct Graph* grafo, vector<int> vec, int nodo, int cantNodosClique){
	int k = 0;
	for(int i = 0; i < grafo->listaAdy[nodo].size(); i++){
		if(vec[grafo->listaAdy[nodo][i]] == 1){
			k++;
		}
	}
	bool b = (k == cantNodosClique);
	return b;
}

bool noEstabaEnClique(struct Graph* grafo, vector<int> vec, int nodo){
	if(vec[nodo] == 0){
		return true;
	}else{
		return false;
	}
}

int cantFronterasQueAporta(int tamClique, int grado){
	return grado - (tamClique - 1);
}

int calcFrontera(struct Graph* grafo, vector<int> & solAct){
	int rSize = solAct.size();
	int res = 0 ;
	int tamClique = 0;
	for(int i = 0 ; i < rSize; i ++){
		if(solAct[i] == 1 ) tamClique ++;
	}
	for(int i =  0 ; i < rSize; i ++){
		if(solAct[i] == 1)
		res += cantFronterasQueAporta(tamClique, gradoNodo(grafo, i));
	}
	return res;
	
}



bool nodoFormaCliqueA(struct Graph* grafo, vector<int>& vec, int nodo){
	bool res = true;
	for(int i = 0; i < vec.size(); i++){
		if (vec[i] == 1)
		{
			if(!esVecino(grafo, nodo, i )){
				res = false;
			}
		}
	}
	return res;
}



#endif
