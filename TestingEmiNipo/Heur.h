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

bool nodoFormaClique(struct Graph* grafo, vector<int> vec, int nodo){
	bool res = true;
	for(int i = 0; i < grafo->n; i++){
		if(i != nodo && vec[i] == 1 && grafo->matrizAdy[nodo][i] == 0){
			res = false;
		}
	}
	return res;
}

//ATENCION! ESTA FUNCION FUE MODIFICADA RESPECTO A HEUR1.H
bool nodoFormaCliqueA(struct Graph* grafo, vector<int> vec, int nodo){
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
//ATENCION! ESTA FUNCION FUE MODIFICADA RESPECTO A HEUR1.H

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

bool sonAdyacentes(struct Graph* grafo, int nodo1, int nodo2){
	if(grafo->matrizAdy[nodo1][nodo2] == 1){
		return true;
	}else{
		return false;
	}
}

bool noEstabaEnClique(struct Graph* grafo, vector<int> vec, int nodo){
	if(vec[nodo] == 0){
		return true;
	}else{
		return false;
	}
}

void ParaHeuristica(struct Graph* grafo, int &res, vector<int>& vecAux, vector<int>& vecRes){
	
	int nodoGM = nodoGradoMaximo(grafo);		// arranco por un nodo de grado máximo
	vecAux[nodoGM] = 1;
	int mejorFront = calcFrontera(grafo, vecAux);
	vecRes = vecAux;
	vector<int> vecPasos(grafo->n, 0);
	int posFrontMejor = 0;
	int ultNodoAg = nodoGM;

	// hasta acá O(n^2)

	// necesito 3 vectores ya que uno me tiene que guardar el mejor que tenía antes (que podía ser el de 1 nodo), 
	// otro tiene que ir guardando la mejor sol de 2, y otro servir para calcular las fronteras de todas las posCliques
	// el último no puede ser el mismo que el primero ya que más adelante puede tener menos nodos (el primero)
	for(int i = 0; i < grafo->n; i++){			// este ciclo es O(n^3)
		if(i != nodoGM && sonAdyacentes(grafo, nodoGM, i)){
			vecAux[i] = 1;
			int aux = calcFrontera(grafo, vecAux);
			if(aux > posFrontMejor){
				vecPasos = vecAux;
				posFrontMejor = aux;
				ultNodoAg = i;
			}
			vecAux[i] = 0;
		}
	}
	// luego de este for, en vecPasos me queda la mejor de todas las de 2 nodos.

	if(posFrontMejor > mejorFront){
		vecRes = vecPasos;
		mejorFront = posFrontMejor;
	}
	vecAux = vecPasos;

	// ciclo que analiza hasta que no haya más cliques, siempre agregando al nodo que forma la cliqué de mayor frontera con
	// los que estaban antes
	int ultNodoAux = ultNodoAg;
	bool b = true;
	while(b){			// en el peor caso este ciclo se recorre (n-3) veces
		b = false;
		posFrontMejor = 0;
		for(int i = 0; i++; i < grafo->n){			// O(n^3)
			if(sonAdyacentes(grafo, i, ultNodoAg) && noEstabaEnClique(grafo, vecPasos, i) && nodoFormaClique(grafo, vecPasos, i)){
				b = true;
				vecAux[i] = 1;
				int frontAux = calcFrontera(grafo, vecAux);
				if(frontAux > posFrontMejor){
					posFrontMejor = frontAux;
					vecPasos = vecAux;
					ultNodoAux = i;
				}
				vecAux[i] = 0;
			}
		}
		if(posFrontMejor > mejorFront){
			vecRes = vecPasos;
			mejorFront = posFrontMejor;
		}
		vecAux = vecPasos;
		ultNodoAg = ultNodoAux;
	}

	res = mejorFront;

	// siempre en vecPasos me queda la mejor frontera con X nodos. Luego, esa mejor me va a servir para la cantidad
	// de nodos X+1 por lo que la pongo en vecAux, pero antes de pasar a la próxima iteración actualizo la mejor frontera de todas
}

pair< vector<int> , int> HeuristicaNipo(Graph* grafo){		// total complej: O(n^4)
	int res = 0;
	vector<int> vecAux(grafo->n, 0);
	vector<int> vecRes(grafo->n, 0);

	ParaHeuristica(grafo, res, vecAux, vecRes);

	pair< vector<int> , int> resultado (vecRes, res);

	// cout << "El resultado es " << res << endl;
	// cout << "Los nodos de la clique son: ";
	// mostrarUnosVec(vecRes);
	// int cantUn = cantUnosVec(vecRes);
	// cout << "Tiene " << cantUn << " nodos" << endl;
	// cout << endl;
	return resultado;
}

void ParaHeuristicaEmi(struct Graph* grafo, int &res, vector<int>& vecRes){
	
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
			if (i != j && nodoFormaCliqueA(grafo, vecPasos, NodosOrdenados[j]) ) // Si no es el nodo inicial y forma clique lo agrego
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

pair< vector<int> , int> HeuristicaEmi(Graph* grafo){		// total complej: O(n^3)
	int res = 0;
	vector<int> vecRes(grafo->n, 0);

	ParaHeuristicaEmi(grafo, res, vecRes);

	pair< vector<int> , int> resultado (vecRes, res);
	// cout << "El resultado es " << res << endl;
	// cout << "Los nodos de la clique son: ";
	// mostrarUnosVec(vecRes);
	// int cantUn = cantUnosVec(vecRes);
	// cout << "Tiene " << cantUn << " nodos" << endl;
	// cout << endl;
	return resultado;
}