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

int main(){
	//Test0();
	//Test1();
	//TestX();
	Test2();
	return 0;
}