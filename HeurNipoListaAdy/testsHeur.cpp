#include "../FuerzaBruta/FuerzaBruta.h"
#include "../GeneradorGrafos/GeneradorDeGrafosConClique.h"
#include <fstream>
#include <random>
#include <chrono>

#define DENSIDAD_MEDIA 0.5

using namespace std;

// Recordar que el Test1 de Golosos también se modifica pues ahora por lo menos la función Nipo es O(n * m)
// PULLEAR PARA HEURÍSTICA EMI
// TRADUCTORRRR

void traductorListaAMatriz(Graph* grafoLista, GraphMat* grafoMatriz){

}

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

void Test5_8(){		// es el TP3_test5.n_8.sol
	Graph grafo;
	int n = 8;
	int m = 16;
	createGraph(&grafo, n, m);
	addEdge(&grafo, 0, 1);
	addEdge(&grafo, 0, 2);
	addEdge(&grafo, 0, 3);
	addEdge(&grafo, 0, 4);
	addEdge(&grafo, 0, 5);
	addEdge(&grafo, 0, 6);
	addEdge(&grafo, 0, 7);
	addEdge(&grafo, 1, 5);
	addEdge(&grafo, 1, 7);
	addEdge(&grafo, 2, 3);
	addEdge(&grafo, 2, 5);
	addEdge(&grafo, 3, 6);
	addEdge(&grafo, 3, 7);
	addEdge(&grafo, 4, 5);
	addEdge(&grafo, 4, 7);
	addEdge(&grafo, 6, 7);
	HeuristicaNipo(&grafo);
}


//TEST 1 (LISTO)

void genGraphComp(Graph* grafo, int cantNodos){		// genera un grafo completo de n nodos
	int n = cantNodos;
	int m = n * (n - 1) / 2;
	createGraph(grafo, n, m);

	int k = 0;
	for(int nodo = 0; nodo < n; nodo++){
		for(int dest = nodo + 1; dest < n; dest++){
			addEdge(grafo, nodo, dest);
		}
	}
	
	mostrarGrafo(grafo);
}

void funcionEneCubo(int n){
	int x = 0;
	int y = 0;
	int z = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			y++;
			for(int k = 0; k < n; k++){
				x++;
				z = x + y;
				int w = 37;
			}
		}
	}
}

void expComplej(){	// testea los tiempos de nuestras heurísticas en grafos completos
	fstream s ("ExpComplejHeurNipoHeurEmi.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startEneCubo, endEneCubo;
	std::chrono::time_point<std::chrono::system_clock> startEneCuarta, endEneCuarta;

	cout << "Arranca Exp Complej" << endl;

	for(int i = 1; i < 351; i++){
		cout << "Voy por n = " << i << endl;
		Graph grafo;
		genGraphComp(&grafo, i);
		for(int j = 0; j < 40; j++){ //decia 40
			s << i;
			s << ",";

			pair<vector<int>, int> resultado;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "CompletoHeurNipo" << endl;


			// Ahora todo lo mismo pero con la heurística de Emi
			// s << i;
			// s << ",";

			// pair <vector<int>, int> resultado1;

			// start1 = std::chrono::system_clock::now();
			// resultado1 = HeuristicaEmi(&grafo);
			// end1 = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			// s << resultado1.second;
			// s << ",";

			// s << elapsed_secondsA.count();
			// s << ",";
			// s << "CompletoHeurEmi" << endl;

		}
	}
}

// TEST 2 SE VUELA ASÍ QUE NO HACE FALTA NADA

// TEST 3

void expGrafoTodosContraTodos(){
	srand(60);  //SEMILLA ARBITRARIA PERO SIEMPRE QUE SEA LA MISMA SI SE QUIEREN LOS MISMO GRAFOS

	fstream s ("Test3TodosvsTodos.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca Todos contra todos" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;

	for(int i = 1; i < 35; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 40; j++){ 

			// Algoritmo exacto

			s << i;
			s << ",";

			Graph grafo;
			generadorGrafoRandom(&grafo, i, DENSIDAD_MEDIA, rand(), 0);

			// acá va el traductor de grafo a grafo1 (lista de adyacencias a matriz adyacencias, Graph a GraphMat)

			GraphMat grafo1;

			int resultadoBLN;
			startBLN = std::chrono::system_clock::now();
			resultadoBLN = cliqueMaxFront(&grafo1);
			endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "Exacto" << endl;


			// Ahora heurística Nipo, recordemos que el resultado va a ser la diferencia

			s << i;
			s << ",";
			
			pair<vector<int>, int> resultado;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			resultado.second = resultadoBLN - resultado.second;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "GrafoRandomDMediaHeurNipo" << endl;


			// Ahora heurística Emi, recordemos que el resultado va a ser la diferencia

			s << i;
			s << ",";

			pair <vector<int>, int> resultado1;

			start1 = std::chrono::system_clock::now();
			resultado1 = HeuristicaEmi(&grafo);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			resultado1.second = resultadoBLN - resultado1.second;

			s << resultado1.second;
			s << ",";

			s << elapsed_secondsA.count();
			s << ",";
			s << "GrafoRandomDMediaHeurEmi" << endl;
		}
	}
}

// TEST 4 SE LO DEJO A EMI

// TEST 5 

void expGrafoRandomDensidadMedia(){
	srand(60);  // Es la semilla por la que arranca el generador de grafos en cada iteración. Que sea siempre la misma

	fstream s ("ExpGrafosRandomFinales.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo Random Densidad Media" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	// std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	// std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 1; i < 401; i = i + 10){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 40; j++){ 
			s << i;
			s << ",";

			Graph grafo;
			generadorGrafoRandom(&grafo, i, DENSIDAD_MEDIA, rand(), 0);
			
			pair<vector<int>, int> resultado;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "GrafoRandomDMediaHeurNipo" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo

			// s << i;
			// s << ",";

			// int resultadoBLN;
			//  startBLN = std::chrono::system_clock::now();
			//  resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado.first);
			//  endBLN = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			// s << resultadoBLN;
			// s << ",";

			// s << elapsed_secondsBLN.count();
			// s << ",";
			// s << "GrafoRandomDMediaHeurGregoNippo" << endl;


			//Ahora todo lo mismo pero con la heurística de Emi

			s << i;
			s << ",";

			pair <vector<int>, int> resultado1;

			start1 = std::chrono::system_clock::now();
			resultado1 = HeuristicaEmi(&grafo);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			s << resultado1.second;
			s << ",";

			s << elapsed_secondsA.count();
			s << ",";
			s << "GrafoRandomDMediaHeurEmi" << endl;


			// s << i;
			// s << ",";

			// resultadoBLN;
			//  startBLN = std::chrono::system_clock::now();
			//  resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado1.first);
			//  endBLN = std::chrono::system_clock::now();

			//  elapsed_secondsBLN = endBLN-startBLN;

			// s << resultadoBLN;
			// s << ",";

			// s << elapsed_secondsBLN.count();
			// s << ",";
			// s << "GrafoRandomDMediaHeurGregoEmi" << endl;


			//Ahora todo lo mismo pero con la heurística d

		}
	}
}




// void genGrafoMalo(Graph* grafo, int cantNodos){		// n >= 5, sino tira segmentation fault
// 	int n = cantNodos;
// 	int m = cantNodos - 2;

// 	createGraph(grafo, n, m);

// 	int r, v;

// 	if(n % 3 == 2){
// 		r = (n + 1) / 3;
// 		v = r - 2;
// 		int i = 1;
// 		for(int j = 0; j < r; j++){
// 			addEdge(grafo, 0, i);
// 			i++;
// 		}
// 		addEdge(grafo, i, i + 1);
// 		for(int j = i + 2; j < (i + 2) + v; j++){
// 			addEdge(grafo, i, j);
// 		}
// 		i++;
// 		for(int j = i + 1 + v; j < (i + 1 + v*2); j++){
// 			addEdge(grafo, i, j);
// 		}
// 	}else{
// 		if(n % 3 == 0){
// 			r = n / 3;
// 			v = r - 2;
// 			int i = 1;
// 			for(int j = 0; j < r; j++){
// 				addEdge(grafo, 0, i);
// 				i++;
// 			}
// 			addEdge(grafo, i, i + 1);
// 			for(int j = i + 2; j < (i + 2) + v; j++){
// 				addEdge(grafo, i, j);
// 			}
// 			i++;
// 			for(int j = i + 1 + v; j < (i + 1 + v*2); j++){
// 				addEdge(grafo, i, j);
// 			}
// 			addEdge(grafo, n - 1, n - 2);
// 		}else{
// 			r = (n - 1) / 3;
// 			v = r - 2;
// 			int i = 1;
// 			for(int j = 0; j < r; j++){
// 				addEdge(grafo, 0, i);
// 				i++;
// 			}
// 			addEdge(grafo, i, i + 1);
// 			for(int j = i + 2; j < (i + 2) + v; j++){
// 				addEdge(grafo, i, j);
// 			}
// 			i++;
// 			for(int j = i + 1 + v; j < (i + 1 + v*2); j++){
// 				addEdge(grafo, i, j);
// 			}
// 			addEdge(grafo, n - 2, n - 3);
// 			addEdge(grafo, n - 1, 1);
// 		}
// 	}
// 	// mostrarMatriz(grafo->matrizAdy, n);
// }

// void expGrafoMalo(){
// 	fstream s ("ExpGrafoMaloHeurNipo.csv", ios::out);

// 	s << "cantNod,Res,Tiempo,Tipo" << endl;

// 	cout << "Arranca grafo malo Nipo" << endl;

// 	std::chrono::time_point<std::chrono::system_clock> start, end;

// 	for(int i = 5; i < 601; i++){
// 		cout << "Voy por n = " << i << endl;
// 		for(int j = 0; j < 40; j++){
// 			s << i;
// 			s << ",";

// 			Graph grafo;
// 			genGrafoMalo(&grafo, i);

// 			pair<vector<int>, int> resultado;

// 			start = std::chrono::system_clock::now();
// 			resultado = HeuristicaNipo(&grafo);
// 			end = std::chrono::system_clock::now();

// 			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

// 			s << resultado.second;
// 			s << ",";

// 			s << elapsed_seconds.count();
// 			s << ",";
// 			s << "GrafoMaloNipo" << endl;
// 		}
// 	}
// }





int main(){
	// Test1();
	// TestX();
	// Test2();
	Test5_8();

	// Graph grafo;
	// genGrafoMalo(&grafo, 2);
	// Graph grafo1;
	// genGrafoMalo(&grafo1, 3);
	// Graph grafo2;
	// genGrafoMalo(&grafo2, 4);
	// expGrafoMalo();
	return 0;
}