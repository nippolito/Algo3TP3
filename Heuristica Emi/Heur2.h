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



//ATENCION! ESTA FUNCION FUE MODIFICADA RESPECTO A HEUR1.HPP
bool nodoFormaClique(struct Graph* grafo, vector<int> vec, int nodo){
	bool res = true;
	for(int i = 0; i < vec.size(); i++){
		if (vec[i] == 1)
		{
			if(i != nodo && grafo->matrizAdy[nodo][i] == 0){
				res = false;
			}
		}

	}
	//cout << "se agrego el " << nodo << endl;
	return res;
}
//ATENCION! ESTA FUNCION FUE MODIFICADA RESPECTO A HEUR1.HPP




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


bool sortByGrade(int i, int j, Graph* grafo){
		return(gradoNodo(grafo, i) > gradoNodo(grafo, j));

	}




void ParaHeuristica(struct Graph* grafo, int &res, vector<int>& vecRes){
	
	//La idea es encontrar la clique maxima y devolver su frontera

	//en VecRes voy a guardar la clique mas grande guardada hasta el momento
	//en VecPasos voy a guardar las cliques formadas por cada iteracion

	//Como encontrar la clique maxima es un problema NP, vamos a implementar una heuristica para obtenerla.
	//Vamos a ordenar los nodos por grado de manera que d(NodosOrdenados[i]) >= d(NodosOrdenados[i+1])
	
	int cantNodosG = grafo->n;
	
	int NodosOrdenados[cantNodosG];
	for (int i = 0; i < cantNodosG; i++)
	{
		NodosOrdenados[i] = i;
	}
	
	for (int i = 0; i < cantNodosG; i++)
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

	/*
	DEBUGGER
	cout << "Nodos Ordenados por grado:" << endl;
	for (int i = 0; i < cantNodosG; i++)
	{
		cout << NodosOrdenados[i] << ", con grado: " << gradoNodo(grafo, NodosOrdenados[i]) << endl;
	}
	*/


	for (int i = 0; i < cantNodosG; i++)
	{
		/*
		if (i == 0)
		{
			cout << "Empieza primera iteracion!" << endl;
		}
		*/
		vector<int> vecPasos(grafo->n, 0); //creo nueva clique
		vecPasos[NodosOrdenados[i]] = 1;
		for (int j = 0; j < cantNodosG; j++) //Itero en orden de grado
		{
			if (i != j && nodoFormaClique(grafo, vecPasos, NodosOrdenados[j]) ) // Si no es el nodo inicial y forma clique lo agrego
			{
				vecPasos[NodosOrdenados[j]] = 1;
			}
		}

		/*
		if (i == 0)
		{
			cout << "Clique final primera iteracion: " << endl;
			cout << "En iteracion " << i << " la clique parcial es:" << endl;
			for (int k = 0; k < cantNodosG; k++)
			  {
			  	cout << k << ": " << vecPasos[k] << endl;
			  }
			  cout<< endl;
			  cout<< endl;
			  cout<< endl;
			  cout<< endl;
			  cout<< endl;
		}
		*/

		if (cantNodos(vecRes) < cantNodos(vecPasos)) //Si la clique creada es mas grande que la maxima guardada la reemplazo
		{
			vecRes = vecPasos;
		}else if(cantNodos(vecRes) == cantNodos(vecPasos)){ //Si la clique creada es igual de grande que la guardada, pero con mayor frontera, la reemplazo.

			if (calcFrontera(grafo, vecPasos) > calcFrontera(grafo, vecRes))
			{
				vecRes = vecPasos;
			}
		}

		/*
		cout << "En iteracion " << i << " la clique parcial es:" << endl;
		for (int k = 0; k < cantNodosG; k++)
		  {
		  	cout << k << ": " << vecRes[k] << endl;
		  }
		*/
		 
	}

	res = calcFrontera(grafo, vecRes);

}

void HeuristicaEmi(Graph* grafo){		// total complej: O(n^3)
	int res = 0;
	vector<int> vecRes(grafo->n, 0);

	ParaHeuristica(grafo, res, vecRes);
	cout << "El resultado es " << res << endl;
	cout << "Los nodos de la clique son: ";
	mostrarUnosVec(vecRes);
	int cantUn = cantUnosVec(vecRes);
	cout << "Tiene " << cantUn << " nodos" << endl;
	cout << endl;
}

/*
int main(){
	return 0;
}
*/

/* Unused functions

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

bool noEstabaEnClique(struct Graph* grafo, vector<int> vec, int nodo){
	if(vec[nodo] == 0){
		return true;
	}else{
		return false;
	}
}

bool sonAdyacentes(struct Graph* grafo, int nodo1, int nodo2){
	if(grafo->matrizAdy[nodo1][nodo2] == 1){
		return true;
	}else{
		return false;
	}
}

*/