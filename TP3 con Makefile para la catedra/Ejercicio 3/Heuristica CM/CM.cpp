#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility>

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

int calcFrontera(struct Graph* grafo, vector<int>& vec){
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

bool nodoFormaClique(struct Graph* grafo, vector<int>& vec, int nodo){
	bool res = true;
	for(int i = 0; i < grafo->n; i++){
		if(i != nodo && vec[i] == 1 && grafo->matrizAdy[nodo][i] == 0){
			res = false;
		}
	}
	return res;
}

//ATENCION! Esta funcion es escencialmente identica a nodoFormaClique
bool nodoFormaCliqueA(struct Graph* grafo, vector<int>& vec, int nodo){
	bool res = true;
	for(int i = 0; i < vec.size(); i++){
		if (vec[i] == 1)
		{
			if(i != nodo && grafo->matrizAdy[nodo][i] == 0){
				res = false;
			}
		}

	}
	return res;
}


int cantNodos(vector<int> nodos){
	int res = 0;
	for (int i = 0; i < nodos.size(); i++)
	{
		if (nodos[i] == 1)
		{
			res++;
		}
	}
	return res;
}




void ParaHeuristicaCM(struct Graph* grafo, int &res, vector<int>& vecRes){
	
	//La idea es encontrar la clique maxima y devolver su frontera

	//en VecRes voy a guardar la clique mas grande guardada hasta el momento
	//en VecPasos voy a guardar las cliques formadas por cada iteracion

	//Como encontrar la clique maxima es un problema NP, vamos a implementar una heuristica para obtenerla.
	//Vamos a ordenar los nodos por grado de manera que d(NodosOrdenados[i]) >= d(NodosOrdenados[i+1])
	
	int cantNodosG = grafo->n;
	
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



	for (int i = 0; i < cantNodosG; i++) //	Paso 3  -  Paso 6
	{
	
		vector<int> vecPasos(grafo->n, 0); //creo nueva clique
		vecPasos[NodosOrdenados[i]] = 1;
		for (int j = 0; j < cantNodosG; j++) //Itero en orden de grado
		{
			if (i != j && nodoFormaCliqueA(grafo, vecPasos, NodosOrdenados[j]) ) // Si no es el nodo inicial y forma clique lo agrego
			{
				vecPasos[NodosOrdenados[j]] = 1;
			}
		}


		if (cantNodos(vecRes) < cantNodos(vecPasos)) //Si la clique creada es mas grande que la maxima guardada la reemplazo
		{
			vecRes = vecPasos;
		}else if(cantNodos(vecRes) == cantNodos(vecPasos)){ //Si la clique creada es igual de grande que la guardada, pero con mayor frontera, la reemplazo.

			if (calcFrontera(grafo, vecPasos) > calcFrontera(grafo, vecRes))
			{
				vecRes = vecPasos;
			}
		}

		 
	}

	res = calcFrontera(grafo, vecRes);

}

pair< vector<int> , int> HeuristicaCM(Graph* grafo){		// total complej: O(n^3)
	int res = 0;
	vector<int> vecRes(grafo->n, 0);

	ParaHeuristicaCM(grafo, res, vecRes);

	pair< vector<int> , int> resultado (vecRes, res);

	return resultado;
}

int main(){


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

		pair< vector<int> , int> res = HeuristicaCM(&grafo);



		cout << res.second << " " << cantNodos(res.first)  << " ";
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