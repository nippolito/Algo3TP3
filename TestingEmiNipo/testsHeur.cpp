//#include "Heur.h" SE INCLUYE EN BUSQUEDALOCAL.H
#include "../BusquedaLocal/BusquedaLocalLineal.h"
#include "../FuerzaBruta/FuerzaBruta.h"
#include "../GeneradorGrafos/GeneradorDeGrafosConClique.h"
#include <fstream>
#include <random>
#include <chrono>
#include <iostream>

#define DENSIDAD_MEDIA 0.5

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

//TODO: FUNCIONES DE COTA
void todosContraTodosCompleto(){
	// ifstream f("tuvieja.csv"); //Poner el nombre del archivo de entrada ya creado anteriormente!
	fstream o ("todosContraTodosCompleto.txt", ios::out);
	o << "cantNod,Res,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> start2, end2;

	int n = 2;
	int m = n * (n - 1) / 2;

	for (int i = 1; i < 24; i++) //Asegurarse que termina con un -1
	{
		cout << "Voy por n = " << i << endl;
		for (int l = 0; l < 20; l++) // ESTO VARIA SEGUN CUANTAS REPETICIONES QUERES QUE CORRA! Para tiempos puede que sea solo 5.
		{
			o << i;
			o << ",";
		
			Graph grafo;
			genGraphComp(&grafo, i);

			//Ya tengo el grafo armado
			pair<vector<int>, int> resultado;

			start = std::chrono::system_clock::now();
			resultado = HeuristicaNipo(&grafo);
			end = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

			o << resultado.second;
			o << ",";

			o << elapsed_seconds.count();
			o << ",";
			o << "Grafo_Completo_Heur_Nipo" << endl;

			// Ahora todo lo mismo pero con la heurística de Emi
			o << i;
			o << ",";

			pair <vector<int>, int> resultado1;

			start1 = std::chrono::system_clock::now();
			resultado1 = HeuristicaEmi(&grafo);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			o << resultado1.second;
			o << ",";

			o << elapsed_secondsA.count();
			o << ",";
			o << "Grafo_Completo_Heur_Emi" << endl;

			//Y ahora para exacto
			o << i;
			o << ",";

			int resultado2;

			start2 = std::chrono::system_clock::now();
			resultado2 = cliqueMaxFront(&grafo);
			end2 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsB = end2-start2;

			o << resultado2;
			o << ",";

			o << elapsed_secondsB.count();
			o << ",";
			o << "Grafo_Completo_Exacto" << endl;

			// cout << "\n\n\n\n" << endl;
			// f >> n;
			
		}
		
	}
	return;
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

	for(int i = 5; i < 501; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 25; j++){ //decia 40
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
			// int resultadoBLN;
			// startBLN = std::chrono::system_clock::now();
			// resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado.first);
			// endBLN = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			// s << resultadoBLN;
			// s << ",";

			// s << elapsed_secondsBLN.count();
			// s << ",";
			// s << "GrafoMaloNipoHeurNipoBL" << endl;


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
			// int resultadoBLE;
			// startBLE = std::chrono::system_clock::now();
			// // resultadoBLE = lineal::BusquedaLocalLineal(&grafo, resultado1.first);
			// endBLE = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLE = endBLE-startBLE;

			// s << resultadoBLE;
			// s << ",";

			// s << elapsed_secondsBLE.count();
			// s << ",";
			// s << "GrafoMaloNipoHeurEmiBL" << endl;

		}
	}
}

void expGrafoMaloEmi(){
	fstream s ("ExpGrafosMalosHeurEmi3.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo malo Emi" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 462; i < 501; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 40; j++){ //decia 40
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
			// int resultadoBLN;
			// startBLN = std::chrono::system_clock::now();
			// resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado.first);
			// endBLN = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			// s << resultadoBLN;
			// s << ",";

			// s << elapsed_secondsBLN.count();
			// s << ",";
			// s << "GrafoMaloEmiHeurNipoBL" << endl;




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
			// int resultadoBLE;
			// startBLE = std::chrono::system_clock::now();
			// resultadoBLE = lineal::BusquedaLocalLineal(&grafo, resultado1.first);
			// endBLE = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLE = endBLE-startBLE;

			// s << resultadoBLE;
			// s << ",";

			// s << elapsed_secondsBLE.count();
			// s << ",";
			// s << "GrafoMaloEmiHeurEmiBL" << endl;

		}
	}
}

void expGrafoMaloGrego(){

	fstream s ("ExpGrafosMalosHeurGrego.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo malo Grego" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 5; i < 501; i++){
		cout << "Voy por n = " << i << endl;
		Graph grafo;
		genGrafoMaloNipo(&grafo, i);
		for(int j = 0; j < 25; j++){ //decia 40
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
			s << "GrafoMaloNipoHeurNipo" << endl;


			//Busqueda Local con resultado de la Heuristica Nipo
			int resultadoBLN;
			 startBLN = std::chrono::system_clock::now();
			 resultadoBLN = lineal::BusquedaLocalLineal(&grafo, resultado.first);
			 endBLN = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			// s << resultadoBLN;
			// s << ",";

			// s << elapsed_secondsBLN.count();
			// s << ",";
			// s << "GrafoMaloNipoHeurNipoBL" << endl;


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
			// int resultadoBLE;
			// startBLE = std::chrono::system_clock::now();
			// // resultadoBLE = lineal::BusquedaLocalLineal(&grafo, resultado1.first);
			// endBLE = std::chrono::system_clock::now();

			// std::chrono::duration<double, std::milli> elapsed_secondsBLE = endBLE-startBLE;

			// s << resultadoBLE;
			// s << ",";

			// s << elapsed_secondsBLE.count();
			// s << ",";
			// s << "GrafoMaloNipoHeurEmiBL" << endl;

		}
	}
}

void expGrafoRandomDensidadMedia(){
	srand(125);  //SEMILLA ARBITRARIA PERO SIEMPRE QUE SEA LA MISMA SI SE QUIEREN LOS MISMO GRAFOS

	fstream s ("ExpGrafosRandomN250a400.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo Random Densidad Media" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 251; i < 401; i++){
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

void grafosMalosResultadoExactoNipo(){
	fstream s ("ResultadosGrafoMaloNipo.csv", ios::out);

	s << "cantNod,Res,Tipo" << endl;

	int k = 6;
	for(int i = 14; i < 550; i++){
		s << i;
		s << ",";
		if(i % 3 == 2){
			s << k;
			s << ",";
			s << "Resultado" << endl;
		}else{
			if(i % 3 == 0){
				s << k;
				s << ",";
				s << "Resultado" << endl;
			}else{
				s << k;
				k = k + 2;
				s << ",";
				s << "Resultado" << endl;
			}
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

void funcionEneCuarta(int n){
	int x = 0;
	int y = 0;
	int z = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				z++;
				for(int a = 0; a < n; a++){
					x++;
					y = z + x;
				}
			}
		}
	}
}

void expComplej(){	// testea los tiempos de nuestras heurísticas en grafos completos y los tiempos de las funciones de complejidad
	fstream s ("ExpComplej2.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startEneCubo, endEneCubo;
	std::chrono::time_point<std::chrono::system_clock> startEneCuarta, endEneCuarta;

	cout << "Arranca Exp Complej" << endl;

	for(int i = 362; i < 401; i++){
		cout << "Voy por n = " << i << endl;
		Graph grafo;
		genGraphComp(&grafo, i);
		for(int j = 0; j < 10; j++){ //decia 40
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
			s << "CompletoHeurEmi" << endl;


			// Ahora todo lo mismo con la función Ene cubo
			s << i;
			s << ",";

			startEneCubo = std::chrono::system_clock::now();
			funcionEneCubo(i);
			endEneCubo = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsEneCubo = endEneCubo - startEneCubo;

			s << 0;
			s << ",";

			s << elapsed_secondsEneCubo.count();
			s << ",";
			s << "FuncionEneCubo" << endl;



			// Ahora todo lo mismo con la función Ene cuarta
			s << i;
			s << ",";

			startEneCuarta = std::chrono::system_clock::now();
			funcionEneCuarta(i);
			endEneCuarta = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsEneCuarta = endEneCuarta - startEneCuarta;

			s << 0;
			s << ",";

			s << elapsed_secondsEneCuarta.count();
			s << ",";
			s << "FuncionEneCuarta" << endl;
		}
	}
}

void expGrafoTodosContraTodos(){
	srand(54);  //SEMILLA ARBITRARIA PERO SIEMPRE QUE SEA LA MISMA SI SE QUIEREN LOS MISMO GRAFOS

	fstream s ("NoPuedeSerTanBueno.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca Todos contra todos" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;

	for(int i = 37; i < 38; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 5; j++){ 
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


			// Ahora algoritmo exacto

			s << i;
			s << ",";

			int resultadoBLN;
			startBLN = std::chrono::system_clock::now();
			resultadoBLN = cliqueMaxFront(&grafo);
			endBLN = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

			s << resultadoBLN;
			s << ",";

			s << elapsed_secondsBLN.count();
			s << ",";
			s << "Exacto" << endl;



			//Ahora todo lo mismo pero con la heurística de Emi
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
			// s << "GrafoRandomDMediaHeurEmi" << endl;
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
	// expGrafoMaloNipo();
	// expGrafoMaloEmi();
	// expComplej();
	// grafosMalosResultadoExactoNipo();
	//expGrafoMaloGrego();
	// expGrafoTodosContraTodos();
	expGrafoRandomDensidadMedia();
	return 0;
}