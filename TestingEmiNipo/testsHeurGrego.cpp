#include "Heur.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>


using namespace std;

//TODO: FUNCIONES DE COTA
void heurGraphGrego(){
	ifstream f("tuvieja.csv"); //Poner el nombre del archivo de entrada ya creado anteriormente! Puede ser cualquiera creado por grego
	fstream o ("RESULTADOS_GRAFOS_X_GREGO.csv", ios::out);
	//Nota: Reemplazar el nombre del csv por el tipo de grafo de input (Poco denso, mitad denso, etc)
	o << "cantNod,Res,Tiempo,Tipo" << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	std::chrono::time_point<std::chrono::system_clock> start2, end2;

	int n;
	int m;

	f >> n;
	int voyPorN = 0;
	while (n != -1) //Asegurarse que termina con un -1
	{
		voyPorN++;
		cout << "Voy por n = " << voyPorN << endl;
		for (int l = 0; l < 40; l++) // ESTO VARIA SEGUN EL INPUT! Para tiempos puede que sea solo 5.
		{
			o << voyPorN;
			o << ",";
		
			Graph grafo;
			f >> m;
			//cout << "Nodos: " << n <<", Aristas: " << m << endl;
			createGraph(&grafo, n, m);
			int s;
			int d;
				for (int k = 0; k < m; k++)
				{
					f >> s;
					f >> d;
					addEdge(&grafo, s, d);
					//cout << "Se agrego la arista: " << s << "-" << d << endl;
				}

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
			o << "Grafo_GENERADO_X_GREGO_HeurNipo" << endl;

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
			o << "Grafo_GENERADO_X_GREGOHeurEmi" << endl;

			/* EN CASO DE QUERER CORRER FUERZA BRUTA, DESCOMENTAR ESTE PEDAZO DE CODIGO.
			Nota: Recordar que para n>25 esto no termina nunca.

			int resultado2;

			start2 = std::chrono::system_clock::now();
			resultado2 = cliqueMaxFront(&grafo);
			end2 = std::chrono::system_clock::now();

			std::chrono::duration<double, std::milli> elapsed_secondsA = end2-start2;

			o << resultado2;
			o << ",";

			o << elapsed_secondsA.count();
			o << ",";
			o << "Grafo_GENERADO_X_GREGO_Exacto" << endl;


			*/

			cout << "\n" << endl;
			f >> n;
			
		}
		
	}
return;

}
int main(){
	heurGraphGrego();
	
	return 1;
}