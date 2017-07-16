#include <chrono>
#include "../FuerzaBruta/FuerzaBruta.h"
#include "GeneradorDeGrafosConClique.h"
#include <iostream>
#include <fstream>
#include "MetaHeur.cpp"

using namespace std;

Graph GenerarGrafoRandom(Graph g, int n)
{
	g.n = n;
	g.matrizAdy = vector<vector<int> >(g.n, vector<int>(g.n, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			g.matrizAdy[i][j] = rand() % 2;
			g.matrizAdy[j][i] = g.matrizAdy[i][j];
		}
	}
	return g;
}

void Mediciones(int sampleoGrafos)
{
	srand(time(NULL));

	fstream s("HeatMapGrasp.csv", ios::out);
	s << "cantNod,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200" << endl;
	for (int i = 20; i < 501; )
	{
		vector<int> resultados;
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}

		for (int j = 10; j < 201; )
		{
			resultados.push_back(0);
			for (int k = 0; k < sampleoGrafos; ++k)
			{
				Clique res = CalcularCliqueMaxVecinos(grafos[k], 0.5, j);
				resultados[(j-1)/10] += res.numeroVecinos;
			}
			cout << "Calcule para " << i << " nodos y " << j << " iteraciones " << endl;
			
			resultados[(j-1)/10] = resultados[(j-1)/10]/sampleoGrafos;
			j += 10;
		}
		float esperanza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			cout << (j+1)*10 << " " << resultados[j] << endl;;
			esperanza += resultados[j];
		}
		esperanza = esperanza/resultados.size();
		float varianza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			varianza += (resultados[j] - esperanza) * (resultados[j] - esperanza);
		}

		varianza = sqrt(varianza/resultados.size());
		s << i ;
		for (int j = 0; j < resultados.size(); ++j)
		{
			float res = 0;
			if (varianza != 0){
				res = (resultados[j] - esperanza)/varianza;	
			}
			s << ", " << res;
		}
		s << endl;

		i += 20;

	}
	

}

void MedicionesAlfa(int sampleoGrafos)
{
	srand(time(NULL));

	fstream s("HeatMapGraspAlfa.csv", ios::out);
	s << "cantNod,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00" << endl;
	for (int i = 20; i < 501; )
	{
		vector<int> resultados;
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}

		for (int j = 1; j < 21; j++ )
		{
			resultados.push_back(0);
			for (int k = 0; k < sampleoGrafos; ++k)
			{
				Clique res = CalcularCliqueMaxVecinos(grafos[k], (j*0.05), 150);
				resultados[(j-1)] += res.numeroVecinos;
			}
			cout << "Calcule para " << i << " nodos y " << j*0.05 << " = alfa " << endl;
			
			resultados[(j-1)] = resultados[(j-1)]/sampleoGrafos;
		}
		float esperanza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			esperanza += resultados[j];
		}
		esperanza = esperanza/resultados.size();
		float varianza = 0;
		for (int j = 0; j < resultados.size(); ++j)
		{
			varianza += (resultados[j] - esperanza) * (resultados[j] - esperanza);
		}

		varianza = sqrt(varianza/resultados.size());
		s << i ;
		for (int j = 0; j < resultados.size(); ++j)
		{
			float res = 0;
			if (varianza != 0){
				res = (resultados[j] - esperanza)/varianza;	
			}
			s << ", " << res;
		}
		s << endl;

		i += 20;

	}
	

}


void MedicionesIteraciones(int sampleoGrafos, int sizeGrafos)
{
	srand(time(NULL));

	fstream s("HeatMapGraspIter250.csv", ios::out);
	s << "IteracionesFijas,IteracionesReales,Tipo" << endl;
	vector<Graph> grafos;
	for (int j = 0; j < sampleoGrafos; ++j)
	{
		Graph g;
		grafos.push_back(GenerarGrafoRandom(g, sizeGrafos));
	}
	for (int j = 10; j < 201; )
	{
		for (int k = 0; k < sampleoGrafos; ++k)
		{
			Clique res = CalcularCliqueMaxVecinos(grafos[k], 0.25, j);
			s << j << ", " << res.cantIteraciones << ", " << "Iteraciones Reales" << endl;
		}
		cout << "Calcule para " << sizeGrafos << " nodos y " << j << " iteraciones " << endl;
		
		j += 10;
	}
		

	

}


void MedicionesTiempo(int sampleoGrafos)
{
	srand(time(NULL));

	fstream s("RectaTiempo.csv", ios::out);
	s << "cantNod,Tiempo,Tipo" << endl;
	auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    typedef std::chrono::duration<double, std::milli> Duracion;
	
	for (int i = 20; i < 501; )
	{
		double resultados;
		vector<Graph> grafos;
		for (int j = 0; j < sampleoGrafos; ++j)
		{
			Graph g;
			grafos.push_back(GenerarGrafoRandom(g, i));
		}
		
		for (int k = 0; k < sampleoGrafos; ++k)
		{
			start = std::chrono::high_resolution_clock::now();
   			CalcularCliqueMaxVecinos(grafos[k], 0.25, 1);

			finish = std::chrono::high_resolution_clock::now();
	   		Duracion tiempoEjec = finish - start;
		   	
		   	resultados += tiempoEjec.count(); 
		}
		cout << "Calcule para " << i << " nodos " << endl;
		
		resultados = resultados/sampleoGrafos;

		s << i << ", " << resultados << ", " << "GRASP" << endl;
		
		i += 20;

	}
	

}

void traductorListaAMatriz(GraphTest* grafoLista, Graph* grafoMatriz){
	vector<vector<int > > listAdy = grafoLista->listaAdy;
	grafoMatriz->n = grafoLista->n;
	grafoMatriz->InicializarMatriz();
	for(int i = 0; i < grafoLista->n; i++){
		for(int j = 0; j < listAdy[i].size(); j++){
			grafoMatriz->addEdge( i, listAdy[i][j]);
		}
	}
}

void expGrafoRandomDensidadMedia(){
	srand(60);  // Es la semilla por la que arranca el generador de grafos en cada iteración. Que sea siempre la misma

	fstream s ("ExpGrafosRandomGRASP60.csv", ios::out);

	s << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo Random Densidad Media" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 1; i < 130; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 30; j++){ 
			// s << i;
			// s << ",";

			GraphTest grafo;
			generadorGrafoRandom(&grafo, i, 0.5, rand(), 0);
			Graph grafoMat;
			traductorListaAMatriz(&grafo, &grafoMat);
			
			s << i;
			s << ",";

			start1 = std::chrono::system_clock::now();
			Clique res = CalcularCliqueMaxVecinos(grafoMat, 0.25,200);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			s << res.numeroVecinos;
			s << ",";

			s << elapsed_secondsA.count();
			s << ",";
			s << "Grasp" << endl;


			
		}
	}
}

void expGrafoRandom50(){
	srand(50);  // Es la semilla por la que arranca el generador de grafos en cada iteración. Que sea siempre la misma

	fstream sb ("ExpGrafosRandomGRASP50Baja.csv", ios::out);
	fstream sm ("ExpGrafosRandomGRASP50Media.csv", ios::out);
	fstream sa ("ExpGrafosRandomGRASP50Alta.csv", ios::out);

	sb << "cantNod,Res,Tiempo,Tipo" << endl;
	sm << "cantNod,Res,Tiempo,Tipo" << endl;
	sa << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca grafo Random Densidades variadas" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;
	std::chrono::time_point<std::chrono::system_clock> startBLE, endBLE;

	for(int i = 1; i < 130; i = i + 5){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 30; j++){ 
			// s << i;
			// s << ",";

			GraphTest grafo1;
			generadorGrafoRandom(&grafo1, i, 0.1, rand(), 0);
			Graph grafoMat1;
			traductorListaAMatriz(&grafo1, &grafoMat1);
			
			sb << i;
			sb << ",";

			start1 = std::chrono::system_clock::now();
			Clique res = CalcularCliqueMaxVecinos(grafoMat1, 0.25,200);
			end1 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end1-start1;

			sb << res.numeroVecinos;
			sb << ",";

			sb << elapsed_secondsA.count();
			sb << ",";
			sb << "GrafoRandomDBajaGRASP" << endl;

			GraphTest grafo2;
			generadorGrafoRandom(&grafo2, i, 0.5, rand(), 0);
			Graph grafoMat2;
			traductorListaAMatriz(&grafo2, &grafoMat2);
			
			sm << i;
			sm << ",";

			start1 = std::chrono::system_clock::now();
			res = CalcularCliqueMaxVecinos(grafoMat2, 0.25,200);
			end1 = std::chrono::system_clock::now();

			elapsed_secondsA = end1-start1;

			sm << res.numeroVecinos;
			sm << ",";

			sm << elapsed_secondsA.count();
			sm << ",";
			sm << "GrafoRandomDMediaGRASP" << endl;

			GraphTest grafo3;
			generadorGrafoRandom(&grafo3, i, 0.8, rand(), 0);
			Graph grafoMat3;
			traductorListaAMatriz(&grafo3, &grafoMat3);
			
			sa << i;
			sa << ",";

			start1 = std::chrono::system_clock::now();
			res = CalcularCliqueMaxVecinos(grafoMat3, 0.25,200);
			end1 = std::chrono::system_clock::now();

			elapsed_secondsA = end1-start1;

			sa << res.numeroVecinos;
			sa << ",";

			sa << elapsed_secondsA.count();
			sa << ",";
			sa << "GrafoRandomDAltaGRASP" << endl;


			
		}
	}
}

void traductorListaAMatrizTest(GraphTest* grafoLista, GraphMat* grafoMatriz){
	vector<vector<int > > listAdy = grafoLista->listaAdy;
	vector<vector<int > > matrizAdy = grafoMatriz->matrizAdy;

	for(int i = 0; i < grafoLista->n; i++){
		for(int j = 0; j < listAdy[i].size(); j++){
			addEdge(grafoMatriz, i, listAdy[i][j]);
		}
	}
}


void TestTodosvsTodosDifer(){
	srand(50);  //SEMILLA ARBITRARIA PERO SIEMPRE QUE SEA LA MISMA SI SE QUIEREN LOS MISMO GRAFOS

	fstream sb ("ExactovsGRASPDiferenciaBaja.csv", ios::out);
	fstream sm ("ExactovsGRASPDiferenciaMedi.csv", ios::out);
	fstream sa ("ExactovsGRASPDiferenciaAlta.csv", ios::out);

	sb << "cantNod,Res,Tiempo,Tipo" << endl;
	sm << "cantNod,Res,Tiempo,Tipo" << endl;
	sa << "cantNod,Res,Tiempo,Tipo" << endl;

	cout << "Arranca Todos contra todos" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> startBLN, endBLN;

	for(int i = 1; i < 36; i++){
		cout << "Voy por n = " << i << endl;
		for(int j = 0; j < 30; j++){ 

			// Algoritmo exacto
			//Alta
			if (i <= 24){
				
				GraphTest grafo;
				generadorGrafoRandom(&grafo, i, 0.8, rand(), 0);
				// acá va el traductor de grafo a grafo1 (lista de adyacencias a matriz adyacencias, Graph a GraphMat)

				GraphMat grafo1;
				Graph grafo2;
				createGraph(&grafo1, grafo.n, grafo.m);
				traductorListaAMatrizTest(&grafo, &grafo1);
				traductorListaAMatriz(&grafo, &grafo2);

				int resultadoBLN;
				startBLN = std::chrono::system_clock::now();
				resultadoBLN = cliqueMaxFront(&grafo1);
				endBLN = std::chrono::system_clock::now();

				std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

				// Ahora heurística Nipo, recordemos que el resultado va a ser la diferencia

				sa << i;
				sa << ",";
				
				pair<vector<int>, int> resultado;

				start = std::chrono::system_clock::now();
				Clique res = CalcularCliqueMaxVecinos(grafo2, 0.25, 200);
				end = std::chrono::system_clock::now();

				std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

				res.numeroVecinos = resultadoBLN - res.numeroVecinos;

				sa << res.numeroVecinos;
				sa << ",";

				sa << elapsed_seconds.count();
				sa << ",";
				sa << "GrafoRandomDAltaGRASP" << endl;

			}
			//Media
			if (i <= 30){
				GraphTest grafo;
				generadorGrafoRandom(&grafo, i, 0.5, rand(), 0);
				// acá va el traductor de grafo a grafo1 (lista de adyacencias a matriz adyacencias, Graph a GraphMat)

				
				GraphMat grafo1;
				Graph grafo2;
				createGraph(&grafo1, grafo.n, grafo.m);
				traductorListaAMatrizTest(&grafo, &grafo1);
				traductorListaAMatriz(&grafo, &grafo2);

				int resultadoBLN;
				startBLN = std::chrono::system_clock::now();
				resultadoBLN = cliqueMaxFront(&grafo1);
				endBLN = std::chrono::system_clock::now();

				std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

				// Ahora heurística Nipo, recordemos que el resultado va a ser la diferencia

				sm << i;
				sm << ",";
				
				pair<vector<int>, int> resultado;

				start = std::chrono::system_clock::now();
				Clique res = CalcularCliqueMaxVecinos(grafo2, 0.25, 200);
				end = std::chrono::system_clock::now();

				std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

				res.numeroVecinos = resultadoBLN - res.numeroVecinos;

				sm << res.numeroVecinos;
				sm << ",";

				sm << elapsed_seconds.count();
				sm << ",";
				sm << "GrafoRandomDMediaGRASP" << endl;
			}
			//Baja
			if (i <= 35) {
				GraphTest grafo;
				generadorGrafoRandom(&grafo, i, 0.1, rand(), 0);
				// acá va el traductor de grafo a grafo1 (lista de adyacencias a matriz adyacencias, Graph a GraphMat)

				GraphMat grafo1;
				Graph grafo2;
				createGraph(&grafo1, grafo.n, grafo.m);
				traductorListaAMatrizTest(&grafo, &grafo1);
				traductorListaAMatriz(&grafo, &grafo2);

				int resultadoBLN;
				startBLN = std::chrono::system_clock::now();
				resultadoBLN = cliqueMaxFront(&grafo1);
				endBLN = std::chrono::system_clock::now();

				std::chrono::duration<double, std::milli> elapsed_secondsBLN = endBLN-startBLN;

				// Ahora heurística Nipo, recordemos que el resultado va a ser la diferencia

				sb << i;
				sb << ",";
				
				pair<vector<int>, int> resultado;

				start = std::chrono::system_clock::now();
				Clique res = CalcularCliqueMaxVecinos(grafo2, 0.25, 200);
				end = std::chrono::system_clock::now();

				std::chrono::duration<double, std::milli> elapsed_seconds = end-start;

				res.numeroVecinos = resultadoBLN - res.numeroVecinos;

				sb << res.numeroVecinos;
				sb << ",";

				sb << elapsed_seconds.count();
				sb << ",";
				sb << "GrafoRandomDBajaGRASP" << endl;
			}
		}
	}
}


int main(){
	
	cout << "Arrancando Mediciones" << endl;
	//Mediciones(10);
	//MedicionesAlfa(10);
	//MedicionesIteraciones(30, 500);
	//MedicionesIteraciones(30, 250);
	//MedicionesTiempo(30);
	//expGrafoRandomDensidadMedia();
	//expGrafoRandom50();
	
	TestTodosvsTodosDifer();
	return 0;
}