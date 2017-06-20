#include "Heur2.h"
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void Test0(){	// debiera devolver res = 3 y la clique es 0-1-2
	Graph grafo;
	int n = 6;
	int m = 6;
	createGraph(&grafo, n, m);
	//K4
	addEdge(&grafo, 0, 1);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 2, 1);
	addEdge(&grafo, 0, 3);
	addEdge(&grafo, 2, 4);
	addEdge(&grafo, 1, 5);
	

	HeuristicaEmi(&grafo);
}


void Test1(){	// debiera devolver res = 8 y la clique 0-1-2-3
	Graph grafo;
	int n = 10;
	int m = 14;
	createGraph(&grafo, n, m);
	//K4
	addEdge(&grafo, 0, 1);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 0, 3);
	addEdge(&grafo, 1, 2);
	addEdge(&grafo, 1, 3);
	addEdge(&grafo, 3, 2);

	//
	addEdge(&grafo, 0, 4);
	addEdge(&grafo, 0, 6);
	addEdge(&grafo, 2, 7);
	addEdge(&grafo, 4, 2);

	addEdge(&grafo, 1, 5);
	addEdge(&grafo, 3, 5);
	addEdge(&grafo, 1, 8);
	addEdge(&grafo, 3, 9);
	

	HeuristicaEmi(&grafo);
}


void TestX(){ //Encuentra correctamente la clique maxima, pero no es la solucion.
	Graph grafo;
	int n = 6;
	int m = 6;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 2, 1);
	addEdge(&grafo, 2, 3);
	addEdge(&grafo, 3, 5);
	addEdge(&grafo, 2, 5);
	addEdge(&grafo, 5, 4);

	HeuristicaEmi(&grafo);
}

void Test2(){		// No encuentra correctamente la clique maxima. Sin embargo, devuelve una solucion correcta.
	Graph grafo;
	int n = 9;
	int m = 9;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 0, 1);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 0, 3);
	addEdge(&grafo, 0, 4);
	addEdge(&grafo, 0, 5);
	addEdge(&grafo, 2, 6);
	addEdge(&grafo, 7, 6);
	addEdge(&grafo, 7, 8);
	HeuristicaEmi(&grafo);
}

void Test3(){		//El grafo de entrada es completo. La clique maxima es todo el grafo. NO es la solucion correcta
	Graph grafo;
	int n = 3;
	int m = 3;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 0, 1);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 1, 2);
	HeuristicaEmi(&grafo);
}

void TestEstrella(){		//Es el peor caso para la heur 1. Esta heur resuelve el problema.
	Graph grafo;
	int n = 14;
	int m = 12;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 3, 0);
	addEdge(&grafo, 3, 1);
	addEdge(&grafo, 3, 2);
	addEdge(&grafo, 3, 4);
	addEdge(&grafo, 3, 5);

	addEdge(&grafo, 7, 9);
	addEdge(&grafo, 7, 6);
	addEdge(&grafo, 7, 8);
	addEdge(&grafo, 7, 10);

	addEdge(&grafo, 10, 13);
	addEdge(&grafo, 10, 12);
	addEdge(&grafo, 10, 11);
	HeuristicaEmi(&grafo);
}

void TestGen(){ // Se crea un K3. Luego, se van adhiriendo nodos a los nodos 0 y 1, aumentando su grado. Siempre encuentra la clique,
				//pero le pifia por 1 en cada iteracion. 
	Graph grafo;
	int n = 6;
	GeneradorPeorCasoHeur2(&grafo, n);
	HeuristicaEmi(&grafo);
}

int main(){
	//Test0();
	//Test1();
	//TestX();
	//Test2();
	//Test3();
	//TestEstrella();
	//TestGen();
	return 0;
}