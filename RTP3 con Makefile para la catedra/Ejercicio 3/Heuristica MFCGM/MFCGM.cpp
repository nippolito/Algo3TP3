#ifndef HEUR_H
#define HEUR_H

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

pair< vector<int> , int> HeuristicaMFCGM(Graph* grafo){
	int res = 0;
	vector<int> nodosMejorClique(0, 0);

	ParaHeuristica(grafo, res, nodosMejorClique);

	pair< vector<int> , int> resultado (nodosMejorClique, res);

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

		pair< vector<int> , int> res = HeuristicaMFCGM(&grafo);



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
