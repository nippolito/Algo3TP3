#include "FuerzaBruta.h"
#include <fstream>
#include <random>
#include <chrono>

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

void genGraphNigualM(Graph* grafo, int cantNodos){			// grafo con M aristas
	int n = cantNodos;
	int m = cantNodos;

	createGraph(grafo, n, m);

	for(int i = 0; i < n; i++){
		int x1 = rand() % (n - 1);		// rango [0, n - 1]. Nodo i conectado con uno cualquiera no adyacente a él
		bool b = true;
		if(x1 == i){
			if(x1 == n - 1){
				x1--;
			}else{
				x1++;
			}
		}
		while(grafo->matrizAdy[i][x1] == 1 && (b || x1 != 0)){
			if(x1 == n - 1 || !b){
				x1--;
				b = false;
			}
			if(b){
				x1++;
			}
			if(i == x1){
				if(b && x1 != n - 1){
					x1++;
				}else{
					if(!b){
						x1--;
					}else{
						b = false;
						x1--;
					}
				}
			}
		}
		addEdge(grafo, i, x1);
	}

	// mostrarMatriz(grafo->matrizAdy, n);
}

void expGrafosNigualM(){			// testea grafos de N = M, 40 instancias de longitudes entre 2 y 20
	fstream s ("ExpNIgualMNuevaPoda.csv", ios::out);

	s << "cantNod,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;

	for(int i = 2; i < 25; i++){		// testea grafos de N = M
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 40; j++){
			s << i;
			s << ",";

			Graph grafo;
			genGraphNigualM(&grafo, i);

			start = std::chrono::system_clock::now();
			cliqueMaxFront(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << elapsed_seconds.count();
			s << ",";
			s << "NigualM" << endl;
		}
	}
}

void genGraphComp(Graph* grafo, int cantNodos){		// genera un grafo completo de n nodos
	int n = cantNodos;
	int m = n * (n - 1) / 2;
	createGraph(grafo, n, m);

	int k = 0;
	for(int fil = 0; fil < n; fil++){
		for(int col = 0; col < n; col++){
			if(fil != col){
				addEdge(grafo, fil, col);
			}
		}
	}
	
	// mostrarMatriz(grafo->matrizAdy, n);
}

void expGrafosCompletos(){			// testea grafos completos
	fstream s ("ExpCompletoNuevaPoda.csv", ios::out);

	s << "cantNod,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;

	for(int i = 2; i < 25; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 40; j++){
			s << i;
			s << ",";

			Graph grafo;
			genGraphComp(&grafo, i);

			start = std::chrono::system_clock::now();
			int h1 = cliqueMaxFront(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << elapsed_seconds.count();
			s << ",";
			s << "Completo" << endl;
		}
	}
}

void genGraphMitadAristas(Graph* grafo, int cantNodos){		// genera grafo con (n - 1) * (n / 4) aristas aprox
	int n = cantNodos;
	int m;
	if(n % 2 == 0){
		m = n * n / 4;
	}else{
		m = n * ((n - 1) / 2) / 2;
	}
	if(n == 3){
		m = 3;
	}

	createGraph(grafo, n, m);

	for(int fil = 0; fil < n; fil++){
		if(n % 2 == 0){
			int k = 0;
			for(int col = 0; col < n; col++){
				if(grafo->matrizAdy[fil][col] == 1){
					k++;
				}
			}
			int i = rand() % (n - 1);			// rango [0, n - 1]
			while(k < n / 2){
				if(i % n == fil || grafo->matrizAdy[fil][i % n] == 1){
					i++;
				}else{
					int j = i % n;
					addEdge(grafo, fil, j);
					i++;
					k++;						
				}
			}
		}else{
			int k = 0;
			for(int col = 0; col < n; col++){
				if(grafo->matrizAdy[fil][col] == 1){
					k++;
				}
			}
			int i = rand() % (n - 1);			// rango [0, n - 1]
			while(k < (n - 1) / 2) {
				if(i % n == fil || grafo->matrizAdy[fil][i % n] == 1){
					i++;
				}else{
					int j = i % n;
					addEdge(grafo, fil, j);
					i++;
					k++;						
				}
			}
		}
	}

	// mostrarMatriz(grafo->matrizAdy, n);
}

void expGrafosMitadAristas(){			// testea grafos con la mitad de aristas
	fstream s ("ExpMitadAristasNuevaPoda.csv", ios::out);

	s << "cantNod,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;

	for(int i = 2; i < 25; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 40; j++){
			s << i;
			s << ",";

			Graph grafo;
			genGraphMitadAristas(&grafo, i);

			start = std::chrono::system_clock::now();
			int h1 = cliqueMaxFront(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << elapsed_seconds.count();
			s << ",";
			s << "MitadAristas" << endl;
		}
	}
}

int main(){
	srand (time(NULL));
	// Test1();
	// Test2();
	// TestsPracAlgunos();
	// testsA();
	// expGrafosNigualM();
	// expGrafosMitadAristas();
	// expGrafosCompletos();
	return 0;
}