//#include "Heur.h" SE INCLUYE EN BUSQUEDALOCAL.H
#include "../BusquedaLocal/BusquedaLocalLineal.h"
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

void Test1(){	// debiera devolver res = 4 y devuelve bien
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
	HeuristicaNipo(&grafo);
}

// test que está en mi cuaderno de teocomp. Grafo con dos comp conex que una es una estrella (donde el nodo del medio tiene grado 5)
// y otra componente conexa donde todos los nodos son de grado < 5 pero hay una frontera de 6.
// Debiera devolver que el resultado es 5 y OK
void TestX(){
	Graph grafo;
	int n = 14;
	int m = 13;
 	createGraph(&grafo, n, m);
	addEdge(&grafo, 2, 0);
	addEdge(&grafo, 2, 1);
	addEdge(&grafo, 2, 3);
	addEdge(&grafo, 2, 4);
	addEdge(&grafo, 2, 5);
	addEdge(&grafo, 8, 9);
	addEdge(&grafo, 8, 11);
	addEdge(&grafo, 9, 10);
	addEdge(&grafo, 10, 11);
	addEdge(&grafo, 8, 6);
	addEdge(&grafo, 8, 7);
	addEdge(&grafo, 11, 12);
	addEdge(&grafo, 11, 13);

	HeuristicaNipo(&grafo);

	// ahora siendo conexos

	Graph grafo1;
	int n1 = 14;
	int m1 = 14;
 	createGraph(&grafo1, n1, m1);
	addEdge(&grafo1, 2, 0);
	addEdge(&grafo1, 2, 1);
	addEdge(&grafo1, 2, 3);
	addEdge(&grafo1, 2, 4);
	addEdge(&grafo1, 2, 5);
	addEdge(&grafo1, 8, 9);
	addEdge(&grafo1, 8, 11);
	addEdge(&grafo1, 9, 10);
	addEdge(&grafo1, 10, 11);
	addEdge(&grafo1, 8, 6);
	addEdge(&grafo1, 8, 7);
	addEdge(&grafo1, 11, 12);
	addEdge(&grafo1, 11, 13);
	addEdge(&grafo1, 3, 7);

	HeuristicaNipo(&grafo1);
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
	HeuristicaNipo(&grafo);
}

void genGrafoMaloNipo(Graph* grafo, int cantNodos){		// n >= 5, sino tira segmentation fault
	int n = cantNodos;
	int m = cantNodos - 2;

	createGraph(grafo, n, m);

	int r, v;

	if(n % 3 == 2){
		r = (n + 1) / 3;
		v = r - 2;
		int i = 1;
		for(int j = 0; j < r; j++){
			addEdge(grafo, 0, i);
			i++;
		}
		addEdge(grafo, i, i + 1);
		for(int j = i + 2; j < (i + 2) + v; j++){
			addEdge(grafo, i, j);
		}
		i++;
		for(int j = i + 1 + v; j < (i + 1 + v*2); j++){
			addEdge(grafo, i, j);
		}
	}else{
		if(n % 3 == 0){
			r = n / 3;
			v = r - 2;
			int i = 1;
			for(int j = 0; j < r; j++){
				addEdge(grafo, 0, i);
				i++;
			}
			addEdge(grafo, i, i + 1);
			for(int j = i + 2; j < (i + 2) + v; j++){
				addEdge(grafo, i, j);
			}
			i++;
			for(int j = i + 1 + v; j < (i + 1 + v*2); j++){
				addEdge(grafo, i, j);
			}
			addEdge(grafo, n - 1, n - 2);
		}else{
			r = (n - 1) / 3;
			v = r - 2;
			int i = 1;
			for(int j = 0; j < r; j++){
				addEdge(grafo, 0, i);
				i++;
			}
			addEdge(grafo, i, i + 1);
			for(int j = i + 2; j < (i + 2) + v; j++){
				addEdge(grafo, i, j);
			}
			i++;
			for(int j = i + 1 + v; j < (i + 1 + v*2); j++){
				addEdge(grafo, i, j);
			}
			addEdge(grafo, n - 2, n - 3);
			addEdge(grafo, n - 1, 1);
		}
	}
	// mostrarMatriz(grafo->matrizAdy, n);
}

void genPeorCasoEmi(struct Graph* grafo, int n){
	//Genero la cantidad de aristas, en base a la cantidad de nodos que me piden.
	int m;

	if (n == 0 || n == 1){m = 0;};
	if (n == 2){ m = 1;};
	if (n > 2){ m = n;};


	createGraph(grafo, n, m);
	
	if (m == 0){ return;}
	if (m == 1){addEdge(grafo, 0, 1); return;}
	if (m == 3){addEdge(grafo, 0, 1);addEdge(grafo, 0, 2); addEdge(grafo, 1, 2); return;}
	
	if (n > 3)
	{
		addEdge(grafo, 0, 1);
		addEdge(grafo, 0, 2);
		addEdge(grafo, 1, 2);
			
		for (int i = 3; i < n; i++)
		{
			if (i % 2 == 0)
			{
				addEdge(grafo, 0, i);
			} else{
				addEdge(grafo, 1, i);
			}

		}
		return;
	}
}

void expGrafoMaloNipo(){
	fstream s ("ExpGrafosMalosHeurNipo.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo malo Nipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < 601; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 5; j++){ //decia 40
			s << i;
			s << ",";

			Graph grafo;
			genGrafoMaloNipo(&grafo, i);

			pair<vector<int>, int> resultado;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "GrafoMaloNipoHeurNipo" << endl;




			//Busqueda Local con resultado de la Heuristica Nipo
			int resultadoBLN;
			startBLN = std::chrono::system_clock::now();
			resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado.first);
			endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "GrafoMaloNipoHeurNipoBL" << endl;





			// Ahora todo lo mismo pero con la heurística de Emi
			s << i;
			s << ",";

			Graph grafo1;
			genGrafoMaloNipo(&grafo1, i);

			pair <vector<int>, int> resultado1;

			start1 = std::chrono::system_clock::now();
			resultado1 = HeuristicaEmi(&grafo);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			s << resultado1.second;
			s << ",";

			s << elapsed_secondsA.count();
			s << ",";
			s << "GrafoMaloNipoHeurEmi" << endl;





			//Busqueda Local con resultado de la Heuristica Emi
			int resultadoBLE;
			startBLE = std::chrono::system_clock::now();
			resultadoBLE = lineal::BusquedaLocalLineal(&grafo, resultado1.first);
			endBLE = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLE = endBLE-startBLE;

			s << resultadoBLE;
			s << ",";

			s << elapsed_secondsBLE.count();
			s << ",";
			s << "GrafoMaloNipoHeurEmiBL" << endl;

		}
	}
}

void expGrafoMaloEmi(){
	fstream s ("ExpGrafosMalosHeurEmi.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo malo Emi" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < 601; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 5; j++){ //decia 40
			s << i;
			s << ",";

			Graph grafo;
			genPeorCasoEmi(&grafo, i);

			pair<vector<int>, int> resultado;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "GrafoMaloEmiHeurNipo" << endl;




			//Busqueda Local con resultado de la Heuristica Nipo
			int resultadoBLN;
			startBLN = std::chrono::system_clock::now();
			resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado.first);
			endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "GrafoMaloEmiHeurNipoBL" << endl;




			// Ahora todo lo mismo pero con la heurística de Emi
			s << i;
			s << ",";

			Graph grafo1;
			genPeorCasoEmi(&grafo1, i);

			pair <vector<int>, int> resultado1;

			start1 = std::chrono::system_clock::now();
			resultado1 = HeuristicaEmi(&grafo);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			s << resultado1.second;
			s << ",";

			s << elapsed_secondsA.count();
			s << ",";
			s << "GrafoMaloEmiHeurEmi" << endl;



			//Busqueda Local con resultado de la Heuristica Emi
			int resultadoBLE;
			startBLE = std::chrono::system_clock::now();
			resultadoBLE = lineal::BusquedaLocalLineal(&grafo, resultado1.first);
			endBLE = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLE = endBLE-startBLE;

			s << resultadoBLE;
			s << ",";

			s << elapsed_secondsBLE.count();
			s << ",";
			s << "GrafoMaloEmiHeurEmiBL" << endl;

		}
	}
}


int main(){
	// Test1();
	// TestX();
	// Test2();
	// Graph grafo;
	// genGrafoMalo(&grafo, 2);
	// Graph grafo1;
	// genGrafoMalo(&grafo1, 3);
	// Graph grafo2;
	// genGrafoMalo(&grafo2, 4);
	expGrafoMaloNipo();
//	expGrafoMaloEmi();
	return 0;
}