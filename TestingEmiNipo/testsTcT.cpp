#include "Heur.h"
#include "FuerzaBruta.cpp"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>


using namespace std;


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
	ifstream f("tuvieja.csv"); //Poner el nombre del archivo de entrada ya creado anteriormente!
	fstream o ("todosContraTodosCompleto.txt", ios::out);
	o << "cantNod,Res,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
		std::chrono::time_point<std::chrono::system_clock> start2, end2;

	int n = 2;
	int m = n * (n - 1) / 2;

	for (int i =0; i < 25; i++;) //Asegurarse que termina con un -1
	{
		cout << "Voy por n = " << i << endl;
		for (int l = 0; l < 40; l++) // ESTO VARIA SEGUN CUANTAS REPETICIONES QUERES QUE CORRA! Para tiempos puede que sea solo 5.
		{
			o << voyPorN;
			o << ",";
		
			Graph grafo;
			genGraphComp(&grafo, i)

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
			o << voyPorN;
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
			o << voyPorN;
			o << ",";

			int resultado2;

			start2 = std::chrono::system_clock::now();
			resultado2 = cliqueMaxFront(&grafo);
			end2 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end2-start2;

			o << resultado2;
			o << ",";

			o << elapsed_secondsA.count();
			o << ",";
			o << "Grafo_Completo_Exacto" << endl;

			cout << "\n\n\n\n" << endl;
			f >> n;
			
		}
		
	}
return;
}





int main(){
	return 1;
}