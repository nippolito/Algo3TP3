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

void mostrarGrafo(Graph* grafo){
	for(int nodo = 0; nodo < grafo->n; nodo++){
		mostrarVector(grafo->listaAdy[nodo]);
	}
}

void mostrarGrafoMat(GraphMat* grafo){
	for(int nodo = 0; nodo < grafo->n; nodo++){
		mostrarVector(grafo->matrizAdy[nodo]);
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
	bool res = false;
	for(int i = 0; i < grafo->listaAdy[nodo1].size(); i++){
		if(grafo->listaAdy[nodo1][i] == nodo2){
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

int cantFronterasQueAporta(int tamClique, int grado){
	return grado - 2*(tamClique);
}

int calcFrontera(struct Graph* grafo, vector<int> & solAct){
	int rSize = solAct.size();
	int res = 0 ;
	int tamClique = 0;
	for(int i = 0 ; i < rSize; i ++){
		if(solAct[i] == 1 ) tamClique ++;
	}
	for(int i =  0 ; i < rSize; i ++){
		res += cantFronterasQueAporta(tamClique, gradoNodo(grafo, solAct[i]));
	}
	
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


		int fronterasParcial = calcFrontera(grafo, vecPasos);
		if (res < fronterasParcial) //Si la clique creada es mas grande que la maxima guardada la reemplazo
		{
			vecRes = vecPasos;
			res = fronterasParcial;
		
		}		 
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