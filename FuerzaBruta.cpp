#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

struct Graph 			    // n-> Number of vertices, m-> Number of edges
{
    int n, m;
    vector<vector<int> > matrizAdy;		   // graph se representa con matriz de adyacencia
};

void createGraph(Graph* graph, int n, int m){

	graph->n = n;
	graph->m = m;

	vector<vector<int> > matriz(n, vector<int> (n, 0));

	graph->matrizAdy = matriz;
}

void addEdge(struct Graph* grafo, int src, int dest){
	grafo->matrizAdy[src][dest] = 1;
	grafo->matrizAdy[dest][src] = 1;
}

void mostrarMatriz(std::vector<std::vector<int> >& matriz, int n){
	for(int fila = 0; fila < n; fila++){
		for(int column = 0; column < n; column++){
			if(column == 0){
				cout << "[" << matriz[fila][column];
			}else{
				if(column > 0 && column < n-1){
					cout << ", " << matriz[fila][column];
				}else{
					cout << ", " << matriz[fila][column] << "]" << endl;
				}
			}
		}
	}
}

void mostrarVec(vector<int>& vec){
	cout << "[";
	for(int i = 0; i < vec.size(); i++){
		if(i < vec.size() - 1){
			cout << vec[i] << ", ";		
		}else{
			cout << vec[i] << "]" << endl;
		}
	}
}

void mostrarUnosVec(vector<int>& vec){
	cout << "[";
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == 1){
			cout << i << ", ";
		}
	}
	cout << "]" << endl;
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

int gradoNodo(struct Graph* grafo, int nodo){
	int res = 0;
	for(int j = 0; j < grafo->n; j++){
		if(grafo->matrizAdy[nodo][j] == 1){
			res++;
		}
	}
	return res;
}

bool esClique(struct Graph* grafo, vector<int>& vec){
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

int calcFrontera(struct Graph* grafo, vector<int> vec){
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

// auxiliar. La función de backtracking clásica
void cliqueMaxFrontAux(struct Graph* grafo, int n, int ite, vector<int>& vecAux, int &res, vector<int>& vecRes){
	if(ite == n){
		if(esClique(grafo, vecAux)){		// si es cliqué, entonces me fijo si tiene frontera mayor
			mostrarVec(vecAux);
			int cant = calcFrontera(grafo, vecAux); 
			// cout << "La cant es: " << cant << endl;
			if(cant > res){
				res = cant;
				vecRes = vecAux;
			}
		}
	}
	if(ite < n){
		cliqueMaxFrontAux(grafo, n, ite + 1, vecAux, res, vecRes);	// caso recursivo no usar nodo
		vector<int> copia = vecAux;
		copia[ite] = 1;
		cliqueMaxFrontAux(grafo, n, ite + 1, copia, res, vecRes);	// caso recursivo usar nodo
	}
}

// calcula la cliqué de maxima frontera
int cliqueMaxFront(struct Graph* grafo){
	int n = grafo->n;
	vector<int> vecRes(n);
	vector<int> vecAux(n);
	int res = 0;
	cliqueMaxFrontAux(grafo, n, 0, vecAux, res, vecRes);	// función auxiliar que hace todo
	cout << "El resultado es " << res << endl;
	cout << "Los nodos de la clique son: ";
	mostrarUnosVec(vecRes);
	int cantUn = cantUnosVec(vecRes);
	cout << "Tiene " << cantUn << " nodos" << endl;
	cout << endl;
	return 0;
}

void Test1(){		// debe dar que son los nodos 2 y 3, y res = 4
	Graph grafo;
	int n = 6;
	int m = 6;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 2, 1);
	addEdge(&grafo, 2, 3);
	addEdge(&grafo, 3, 5);
	addEdge(&grafo, 3, 4);
	addEdge(&grafo, 5, 4);
	cliqueMaxFront(&grafo);
}

void Test2(){		// debe dar que es el nodo 5 (estrella), y res = 7
	Graph grafo;
	int n = 8;
	int m = 7;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 5, 1);
	addEdge(&grafo, 5, 2);
	addEdge(&grafo, 5, 0);
	addEdge(&grafo, 5, 3);
	addEdge(&grafo, 5, 4);
	addEdge(&grafo, 5, 6);
	addEdge(&grafo, 5, 7);
	cliqueMaxFront(&grafo);
}

int main(){
	Test1();
	Test2();
	// Graph grafo;
	// int n = 5;
	// int m = 3;
	// createGraph(&grafo, n, m);
	// addEdge(&grafo, 1, 4);
	// addEdge(&grafo, 4, 3);
	// addEdge(&grafo, 3, 1);
	// mostrarMatriz(grafo.matrizAdy, grafo.n);
	return 0;
}