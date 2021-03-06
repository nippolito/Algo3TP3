#include "../FuerzaBruta/FuerzaBruta.h"
#include "../GeneradorGrafos/GeneradorDeGrafosConClique.h"
#include "Heur1.h"
#include "../BusquedaLocal/busquedaLocal.h"
#include <fstream>
#include <random>
#include <chrono>

#define DENSIDAD_BAJA 0.1
#define DENSIDAD_MEDIA 0.5
#define DENSIDAD_ALTA 0.8

#define W 200

using namespace std;

// Recordar que el Test1 de Golosos también se modifica pues ahora por lo menos la función Nipo es O(n * m)
// PULLEAR PARA HEURÍSTICA EMI
// TRADUCTORRRR

void quepasaa(){
	Graph grafo;
	createGraph(&grafo, 1, 0);
	vector<int> vec(1, 0);
	vec[0] = 1;
	cout << calcFrontera(&grafo, vec) << endl;
}

void traductorListaAMatriz(Graph* grafoLista, GraphMat* grafoMatriz){
	vector<vector<int > > listAdy = grafoLista->listaAdy;
	vector<vector<int > > matrizAdy = grafoMatriz->matrizAdy;

	for(int i = 0; i < grafoLista->n; i++){
		for(int j = 0; j < listAdy[i].size(); j++){
			addEdge(grafoMatriz, i, listAdy[i][j]);
		}
	}
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

	mostrarGrafo(&grafo);

	GraphMat grafo2;
	createGraph(&grafo2, grafo.n, grafo.m);
	traductorListaAMatriz(&grafo, &grafo2);
	mostrarGrafoMat(&grafo2);
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
	fstream s ("FuncionEneCubo.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startCubo, endCubo;
	std::chrono::time_point<std::chrono::system_clock> startEneCuarta, endEneCuarta;

	cout << "Arranca Exp Complej" << endl;

	for(int i = 1; i < 351; i++){
		cout << "Voy por n = " << i << endl;
		// Graph grafo;
		// genGraphComp(&grafo, i);
		for(int j = 0; j < 30; j++){ //decia 40
			// s << i;
			// s << ",";

			// pair<vector<int>, int> resultado;

			// start = std::chrono::system_clock::now();
			// resultado = HeuristicaNipo(&grafo);
			// end = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			// s << resultado.second;
			// s << ",";

			// s << elapsed_seconds.count();
			// s << ",";
			// s << "CompletoHeurNipo" << endl;


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

			// Ahora funcion Complej

			s << i;
			s << ",";
			s << 0;
			s << ",";

			startCubo = std::chrono::system_clock::now();
			funcionEneCubo(i);
			endCubo = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsCubo = endCubo-startCubo;

			s << elapsed_secondsCubo.count();
			s << ",";
			s << "FuncionEneCubo" << endl;

		}
	}
}

// TEST 2 SE VUELA ASÍ QUE NO HACE FALTA NADA

// TEST 3

void expGrafoTodosContraTodos(){
	srand(60);  //SEMILLA ARBITRARIA PERO SIEMPRE QUE SEA LA MISMA SI SE QUIEREN LOS MISMO GRAFOS

	fstream s ("Test3TodosvsTodosHeurEmiNuevo.csv", ios::out);

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
			createGraph(&grafo1, grafo.n, grafo.m);
			traductorListaAMatriz(&grafo, &grafo1);

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

			// s << i;
			// s << ",";
			
			// pair<vector<int>, int> resultado;

			// start = std::chrono::system_clock::now();
			// resultado = HeuristicaNipo(&grafo);
			// end = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			// resultado.second = resultadoBLN - resultado.second;

			// s << resultado.second;
			// s << ",";

			// s << elapsed_seconds.count();
			// s << ",";
			// s << "GrafoRandomDMediaHeurNipo" << endl;


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

	fstream s ("ExpGrafosRandomEmiNuevo.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo Random Densidad Media" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	// std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	// std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 1; i < 401; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 30; j++){ 
			// s << i;
			// s << ",";

			Graph grafo;
			generadorGrafoRandom(&grafo, i, DENSIDAD_MEDIA, rand(), 0);
			
			// pair<vector<int>, int> resultado;

			// start = std::chrono::system_clock::now();
			// resultado = HeuristicaNipo(&grafo);
			// end = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			// s << resultado.second;
			// s << ",";

			// s << elapsed_seconds.count();
			// s << ",";
			// s << "GrafoRandomDMediaHeurNipo" << endl;


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

void expGolosaNipoVsBLL(){
	srand(60);

	fstream s ("HeurNipoConBL.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Heur Nipo con BL" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < 401; i++){
		cout << "Voy por n = " << i << endl;
		Graph grafo;
		generadorGrafoRandom(&grafo, i, DENSIDAD_MEDIA, rand(), 0);
			
		for(int j = 0; j < 30; j++){ //decia 40
			s << i;
			s << ",";

			pair<vector<int>, int> resultado;
			pair<vector<int>, int> resultadoBLN;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "HeurNipoRandom" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo
			s << i;
			s << ",";
			
			 startBLN = std::chrono::system_clock::now();
			// resultadoBLN = HeurGregoLineal(&grafo, resultado.first);
			 endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN.second;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "BLLinealHeurNipo" << endl;
			
			
			s << i;
			s << ",";
			
			s << resultadoBLN.second - resultado.second;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaGolosaNipoConBL" << endl;


			
		}
	}
}

void expGolosaNipoVsBLC(){
	srand(60);

	fstream s ("HeurNipoConBCuadratica.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Heur Nipo con BL" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < 401; i++){
		cout << "Voy por n = " << i << endl;
		Graph grafo;
		generadorGrafoRandom(&grafo, i, DENSIDAD_MEDIA, rand(), 0);
			
		for(int j = 0; j < 30; j++){ //decia 40
			s << i;
			s << ",";

			pair<vector<int>, int> resultado;
			pair<vector<int>, int> resultadoBLN;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "HeurNipoRandom" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo
			s << i;
			s << ",";
			
			 startBLN = std::chrono::system_clock::now();
			// resultadoBLN = HeurGregoCuadratica(&grafo, resultado.first);
			 endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN.second;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "BLCuadraticaHeurNipo" << endl;
			
			
			s << i;
			s << ",";
			
			s << resultadoBLN.second - resultado.second;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaGolosaNipoConBCuadratica" << endl;


			
		}
	}
}

void expGolosaEmiVsBLDensidadBaja(){
	srand(60);

	fstream s ("HeurEmioConLinealDBaja.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo, Iteraciones" << endl;

	cout << "Heur Emi con BL" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	
	std::chrono::time_point<std::chrono::system_clock> startBLN2, endBLN2;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < W; i+=5){
		cout << "Voy por n = " << i << endl;
		
			
		for(int j = 0; j < 30; j++){ //decia 40
			
			Graph grafo;
			generadorGrafoRandom(&grafo, i, DENSIDAD_BAJA, rand(), 0);
			
			long int iteracionesL = 0 ;
			long int iteracionesC = 0;
			
			s << i;
			s << ",";

			pair<vector<int>, int> resultado;
			pair<vector<int>, int> resultadoBLN;
			pair<vector<int>, int> resultadoBLN2;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaEmi(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "HeurEmi" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo
			s << i;
			s << ",";
			
			 startBLN = std::chrono::system_clock::now();
			 resultadoBLN = HeurGregoLineal(&grafo, resultado.first, iteracionesL);
			 endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN.second;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "BLinealHeurEmi" ;
			s<< ", ";
			s << iteracionesL <<endl;
				
			//////////////////////
			
			s << i;
			s << ",";
			
			s << (double)(resultadoBLN.second - resultado.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaHeurEmiConLineal"<<endl;
			
			

			/////////////////////
			s << i;
			s << ",";
			
			 startBLN2 = std::chrono::system_clock::now();
			 resultadoBLN2 = HeurGregoCuadratica(&grafo, resultado.first, iteracionesC);
			 endBLN2 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN2 = endBLN2-startBLN2;

			s << resultadoBLN2.second;
			s << ",";

			s << elapsed_secondsBLN2.count();
			s << ",";
			s << "BCuadraticaHeurEmi" ;
			s<< ", ";
			s << iteracionesC <<endl;
			
			
			s << i;
			s << ",";
			
			s << (double)(resultadoBLN2.second - resultado.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaHeurEmiConCuadratica" << endl;


			s << i;
			s << ",";
			
			s << (double)(resultadoBLN2.second - resultadoBLN.second) / (double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciasLocales" << endl;



			
		}
	}
}

void expGolosaEmiVsBLDensidadMedia(){
	srand(60);

	fstream s ("HeurEmioConLinealDMedia.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo, Iteraciones" << endl;

	cout << "Heur Emi con BL" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	
	std::chrono::time_point<std::chrono::system_clock> startBLN2, endBLN2;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < W; i+=5){
		cout << "Voy por n = " << i << endl;
		
			
		for(int j = 0; j < 30; j++){ //decia 40
			Graph grafo;
			generadorGrafoRandom(&grafo, i, DENSIDAD_MEDIA, rand(), 0);
			
			long int iteracionesL = 0 ;
			long int iteracionesC = 0;
			
			s << i;
			s << ",";

			pair<vector<int>, int> resultado;
			pair<vector<int>, int> resultadoBLN;
			pair<vector<int>, int> resultadoBLN2;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaEmi(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "HeurEmi" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo
			s << i;
			s << ",";
			
			 startBLN = std::chrono::system_clock::now();
			 resultadoBLN = HeurGregoLineal(&grafo, resultado.first, iteracionesL);
			 endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN.second;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "BLinealHeurEmi";
			s<< ", ";
			s << iteracionesL <<endl;
				
			//////////////////////
			
			s << i;
			s << ",";
			
			s << (double)(resultadoBLN.second - resultado.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaHeurEmiConLineal" << endl;

			/////////////////////
			s << i;
			s << ",";
			
			 startBLN2 = std::chrono::system_clock::now();
			 resultadoBLN2 = HeurGregoCuadratica(&grafo, resultado.first, iteracionesC);
			 endBLN2 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN2 = endBLN2-startBLN2;

			s << resultadoBLN2.second;
			s << ",";

			s << elapsed_secondsBLN2.count();
			s << ",";
			s << "BCuadraticaHeurEmi";
			s<< ", ";
			s << iteracionesC <<endl;
			
			
			s << i;
			s << ",";
			
			s << (double)(resultadoBLN2.second - resultado.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaHeurEmiConCuadratica" << endl;



			s << i;
			s << ",";
			
			s << (double)(resultadoBLN2.second - resultadoBLN.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciasLocales" << endl;



		}
	}
}

void expGolosaEmiVsBLDensidadAlta(){
	srand(60);

	fstream s ("HeurEmioConLinealDAlta.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo, Iteraciones" << endl;

	cout << "Heur Emi con BL" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	
	std::chrono::time_point<std::chrono::system_clock> startBLN2, endBLN2;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < W; i+=5){
		cout << "Voy por n = " << i << endl;
		
			
		for(int j = 0; j < 30; j++){ //decia 40
			Graph grafo;
			generadorGrafoRandom(&grafo, i, DENSIDAD_ALTA, rand(), 0);
			
			long int iteracionesL = 0 ;
			long int iteracionesC = 0;
			
			s << i;
			s << ",";

			pair<vector<int>, int> resultado;
			pair<vector<int>, int> resultadoBLN;
			pair<vector<int>, int> resultadoBLN2;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaEmi(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			s << resultado.second;
			s << ",";

			s << elapsed_seconds.count();
			s << ",";
			s << "HeurEmi" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo
			s << i;
			s << ",";
			
			 startBLN = std::chrono::system_clock::now();
			 resultadoBLN = HeurGregoLineal(&grafo, resultado.first, iteracionesL);
			 endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN.second;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "BLinealHeurEmi";
			s<< ", ";
			s << iteracionesL <<endl;
				
			//////////////////////
			
			s << i;
			s << ",";
			
			s << (double)(resultadoBLN.second - resultado.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaHeurEmiConLineal" << endl;

			/////////////////////
			s << i;
			s << ",";
			
			 startBLN2 = std::chrono::system_clock::now();
			 resultadoBLN2 = HeurGregoCuadratica(&grafo, resultado.first, iteracionesC);
			 endBLN2 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN2 = endBLN2-startBLN2;

			s << resultadoBLN2.second;
			s << ",";

			s << elapsed_secondsBLN2.count();
			s << ",";
			s << "BCuadraticaHeurEmi";
			s<< ", ";
			s << iteracionesC <<endl;
			
			
			s << i;
			s << ",";
			
			s << (double)(resultadoBLN2.second - resultado.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciaHeurEmiConCuadratica" << endl;

			s << i;
			s << ",";
			
			s << (double)(resultadoBLN2.second - resultadoBLN.second)/(double)i;
			s << ",";

			s << 0;
			s << ",";
			s << "DiferenciasLocales" << endl;


			
		}
	}
}

void comentarios(){


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



}

int main(){
	// Test1();
	// TestX();
	// Test2();
	// Test5_8();
	//expComplej();
	//expGrafoTodosContraTodos();
	//expGrafoRandomDensidadMedia();
	// quepasaa();
	//expGolosaNipoVsBLL();
	//expGolosaNipoVsBLC();
	
	expGolosaEmiVsBLDensidadBaja();
	expGolosaEmiVsBLDensidadMedia();
	expGolosaEmiVsBLDensidadAlta();

	return 0;
}
