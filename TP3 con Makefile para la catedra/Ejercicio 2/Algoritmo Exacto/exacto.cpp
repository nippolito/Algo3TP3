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


// tiene una pequeña poda: NO va a la rama que corresponde a "usar el nodo" si no es adyacente al último usado (ya que no llevaría a una cliqué)
void cliqueMaxFrontAux(struct Graph* grafo, int n, int ite, int ultUsado, vector<int>& vecAux, int &res, vector<int>& vecRes){
	if(ite == n){
		if(esClique(grafo, vecAux)){		// si es cliqué, entonces me fijo si tiene frontera mayor
			int cant = calcFrontera(grafo, vecAux); 
			if(cant > res){
				res = cant;
				vecRes = vecAux;
			}
		}
	}
	if(ite < n){
		if(ultUsado == -1){
			cliqueMaxFrontAux(grafo, n, ite + 1, ultUsado, vecAux, res, vecRes);	// caso recursivo no usar nodo
			vector<int> copia = vecAux;
			copia[ite] = 1;
			cliqueMaxFrontAux(grafo, n, ite + 1, ite, copia, res, vecRes);	// caso recursivo usar nodo			
		}else{
			if(grafo->matrizAdy[ite][ultUsado] == 0){		// si no es adyacente al último nodo usado, entonces podá
				cliqueMaxFrontAux(grafo, n, ite + 1, ultUsado, vecAux, res, vecRes);	// caso recursivo no usar nodo
			}else{
				cliqueMaxFrontAux(grafo, n, ite + 1, ultUsado, vecAux, res, vecRes);	// caso recursivo no usar nodo
				vector<int> copia = vecAux;
				copia[ite] = 1;
				cliqueMaxFrontAux(grafo, n, ite + 1, ite, copia, res, vecRes);	// caso recursivo usar nodo	
			}
		}
	}
}

pair< vector<int> , int>  cliqueMaxFront(struct Graph* grafo){
	int n = grafo->n;
	vector<int> vecRes(n);
	vector<int> vecAux(n);
	int res = 0;
	cliqueMaxFrontAux(grafo, n, 0, -1, vecAux, res, vecRes);	// función auxiliar que hace todo

	pair< vector<int> , int> resultado (vecRes, res);


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

		pair< vector<int> , int> res = cliqueMaxFront(&grafo);



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
