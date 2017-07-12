#ifndef GENERADOR_GRAFOS_H
#define GENERADOR_GRAFOS_H

#include <iostream>
#include <stdlib.h>
#include <set>
#include <map>
#include <utility>
#include <stdio.h>
#include "../HeurNipoListaAdy/Heur1.h"
#include "../BusquedaLocal/busquedaLocal.h"

using namespace std;

bool EstanDefinidos(set<int> set[], int c1, int c2){
	return (set[c1].find(c2) != set[c1].end());
}

void generadorGrafoRandom(Graph* grafo, int n, double densidad, int semilla,int c){
	
	srand (semilla);	 

	
	bool matrix [n][n];
	for(int i = 0; i < n; i ++){
		for(int j = 0 ; j < n; j++) matrix [i][j] = false;
	}

	int cantAristasEnClique = c*(c-1)/2;
	int cantAristasDisponibles = (n*(n-1)/2) - cantAristasEnClique;
	//cout << "cantAristasDisponibles : "<< cantAristasDisponibles << endl;
	int m = (densidad) *cantAristasDisponibles;


	createGraph(grafo, n, m);
	
	for(int i = 0; i < c ; i ++ ){
		for(int j = i+1; j < c; j++){
			matrix[i][j] = true;
			matrix[j][i] = true;
			addEdge(grafo,i,j);
		}
	}
	for(int i = 0; i < m ; i ++){
		int c1; int c2;
		c1 = rand() % n;
		c2 = rand() % n;

		if( matrix[c1][c2] == true || c1 == c2 ){
			for(int x = n-1 ; x >= 0 ; x --){
				for(int y = x-1 ; y >= 0 ; y --){
					if(!matrix[x][y]){
						c1 = x; c2 = y;
					}
				}
			}
		}

		matrix[c1][c2] = true;
		matrix[c2][c1] = true;
		
		addEdge(grafo,c1,c2);

	}
}

#endif