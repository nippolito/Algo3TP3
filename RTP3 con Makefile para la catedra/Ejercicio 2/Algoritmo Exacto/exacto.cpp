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

bool NoFormaClique(struct GraphMat* grafo, int nodo, vector<int>& vec){
	bool b = false;
	for(int i; i < vec.size(); i++){
		if(vec[i] == 1 && grafo->matrizAdy[i][nodo] == 0){
			b = true;
		}
	}
	return b;
}


void cliqueMaxFrontAux(struct GraphMat* grafo, int n, int ite, vector<int>& vecAux, int &res, vector<int>& vecRes){
	if(ite == n){
		int cant = calcFrontera(grafo, vecAux); 
		if(cant > res){
			res = cant;
			vecRes = vecAux;
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


pair< vector<int>, int> cliqueMaxFront(struct GraphMat* grafo){
	int n = grafo->n;
	vector<int> vecRes(n);
	vector<int> vecAux(n);
	int res = 0;
	cliqueMaxFrontAux(grafo, n, 0, vecAux, res, vecRes);

	pair<vector<int>, int> resultado (vecRes, res);

	return resultado;
}

#endif

int main(){

	cout << "Ingrese los datos como indica el enunciado:" << endl;

	int n;
	cin >> n;

	int m;
	cin >> m;

	if (n > 0){
		GraphMat grafo;
		createGraph(&grafo, n, m);
		int c1, c2;

		for (int i = 0; i < m; i++)
		{
			cin >> c1; cin >> c2;
			addEdge(&grafo, c1-1, c2-1);
		}

		pair< vector<int> , int> res = cliqueMaxFront(&grafo);



		cout << res.second << " " << cantUnosVec(res.first)  << " ";
		for (int i = 0; i < n; i++)
		{
			if (res.first[i] == 1 )
			{
				cout << i + 1 << " ";
			}
			
		}
		cout << endl;
		
	}
	
return 0;


}