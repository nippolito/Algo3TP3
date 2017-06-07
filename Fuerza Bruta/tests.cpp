#include "FuerzaBruta.cpp"
#include <fstream>

using namespace std;

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

void TestsPracAlgunos(){
	Graph grafo;
	int n = 6;
	int m = 6;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 0, 5);
	addEdge(&grafo, 0, 1);
	addEdge(&grafo, 2, 3);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 0, 3);
	addEdge(&grafo, 0, 4);
	cliqueMaxFront(&grafo);	

	Graph grafo1;
	int n1 = 5;
	int m1 = 6;
	createGraph(&grafo1, n1, m1);
	addEdge(&grafo1, 0, 1);
	addEdge(&grafo1, 0, 2);
	addEdge(&grafo1, 0, 3);
	addEdge(&grafo1, 0, 4);
	addEdge(&grafo1, 3, 4);
	addEdge(&grafo1, 2, 4);
	cliqueMaxFront(&grafo1);	

	Graph grafo2;
	int n2 = 4;
	int m2 = 5;
	createGraph(&grafo2, n2, m2);
	addEdge(&grafo2, 1, 3);
	addEdge(&grafo2, 0, 1);
	addEdge(&grafo2, 0, 2);
	addEdge(&grafo2, 0, 3);
	addEdge(&grafo2, 1, 2);
	cliqueMaxFront(&grafo2);
}

void testsA(){		// tiene del 20 al 13 inclusive (el de más arriba es el 20)
	fstream e("TestsPractica.txt", ios::in);
	int m;
	int n;
	e >> n;
	while(n != 0){
		e >> m;
		int sal;
		int dest;
		Graph grafo;
		createGraph(&grafo, n, m);

		for(int i = 0; i < m; i++){
			e >> sal;
			e >> dest;
			addEdge(&grafo, sal - 1, dest - 1);
		}

		cliqueMaxFront(&grafo);

		e >> n;
	}
}


int main(){
	// Test1();
	// Test2();
	// TestsPracAlgunos();
	testsA();
	return 0;
}