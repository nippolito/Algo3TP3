#ifndef BUSQUEDA_LOCAL_LINEAL_H
#define BUSQUEDA_LOCAL_LINEAL_H

#include <iostream>
#include <set>
#include <utility> 
#include "../TestingEmiNipo/Heur.h"

using namespace std;

namespace lineal{
int CalcularFronteras(set<int> matrix [], set<int>& solucion){
	int res = 0;
	for(set<int>::iterator itSol = solucion.begin(); itSol != solucion.end(); itSol ++ ){
		for(set<int>::iterator it = matrix[*itSol].begin(); it != matrix[*itSol].end() ; it++){
			if(solucion.find(*it) == solucion.end()) res ++;
		}
	}

	return res;
}


int BusquedaLocalLinealAux(set<int> matrix [], set<int>& solAct, int n , int m){

	bool noEncontrePozo = true;
	int cantidadDeIteraciones = 0;

	while(noEncontrePozo){
		cantidadDeIteraciones++;
		set<int> solucionesSumandoNodo;
		set<int> solucionesRestandoNodo; 						
		
		pair<int, int> NodoQueMaximizaAgregarUnNodo = pair<int,int>(-1,-1);
		pair<int, int> NodoQueMaximizaSacarUnNodo = pair<int,int>(-1,-1);
		int solucionTalcualEstaba ;

		// guardo las soluciones que surgen de agregarle un nodo
		for(int i = 0; i < n; i ++){
			if(solAct.find(n) == solAct.end()){   // si el nodo no pertenece en la actual solución me fijo si es vecino de todo los que si lo hacen
				bool esVecinoDeTodos = true;
				for(set<int>::iterator it = solAct.begin() ; it != solAct.end(); it++){
					if(matrix[i].find(*it) == matrix[i].end()) esVecinoDeTodos = false;
				}

				if(esVecinoDeTodos){
					solucionesSumandoNodo.insert(i);
				}
			}	
		}
		// guardo las soluciones que surgen de sacarle un nodo
		for(set<int>::iterator it = solAct.begin();it != solAct.end(); it++){  // coomo es una clique le puedo sacar cualquier nodo de la solucion aactual y va a seguir siedno clique
			solucionesRestandoNodo.insert(*it);
		}

		//AHORA QUEDA COMPARA ENTRE LOS VECINOS CUAL ES EL MEJOR

		//me fijo la solucion tal cual estaba
		solucionTalcualEstaba = CalcularFronteras(matrix, solAct);

		// me fijo la mejor solucion vecina  de agregar un nodo
		for(set<int>::iterator it = solucionesSumandoNodo.begin() ; it != solucionesSumandoNodo.end(); it++){
			solAct.insert(*it);
			int aux = CalcularFronteras(matrix, solAct);
			if(aux > NodoQueMaximizaAgregarUnNodo.second ){
				NodoQueMaximizaAgregarUnNodo.first = *it;
				NodoQueMaximizaAgregarUnNodo.second = aux;				
			}
			solAct.erase(*it);
		}
		//me fijo la mejor solucion vecina de eliminar un nodo
		for(set<int>::iterator it = solucionesRestandoNodo.begin(); it != solucionesRestandoNodo.end(); it++){
			solAct.erase(*it);
			int aux = CalcularFronteras(matrix, solAct);
			if(aux > NodoQueMaximizaSacarUnNodo.second){
				NodoQueMaximizaSacarUnNodo.first = *it;
				NodoQueMaximizaSacarUnNodo.second = aux;
			}
			solAct.insert(*it);
		}
		
		if(solucionTalcualEstaba >= NodoQueMaximizaSacarUnNodo.second && solucionTalcualEstaba >= NodoQueMaximizaAgregarUnNodo.second)
			noEncontrePozo = false; // encontre pozo
		else if( NodoQueMaximizaAgregarUnNodo.second >= NodoQueMaximizaSacarUnNodo.second){ // me conviene sumar un nodo
			solAct.insert(NodoQueMaximizaAgregarUnNodo.first);
		}
		else{// me conviene restar un nodo
			solAct.erase(NodoQueMaximizaSacarUnNodo.first);
		}
		
	}
	cout << "Cantidad De Iteraciones : " << cantidadDeIteraciones <<  endl;

	return  CalcularFronteras(matrix, solAct);
}

int BusquedaLocalLineal(Graph* grafo, vector<int>& solAct){
	int n = grafo->n;
	int m = grafo->m;
	set<int> matrix [n];
	for(int i = 0 ; i < n; i++){
		for(int j = 0; j < n; j++){
			if(grafo->matrizAdy[i][j] == 1)
				matrix[i].insert(j);
		}
	}
	set<int> solAct2;
	int solActSize = solAct.size();
	for(int i = 0; i < solActSize; i++){
		if( solAct[i] == 1 ){
		 cout << i <<  " ";
		 solAct2.insert(i);		
		}
	}
	cout << " \n";

	int res =  BusquedaLocalLinealAux(matrix, solAct2, n, m);
	
	solAct.clear();
	for(set<int>::iterator it=solAct2.begin(); it != solAct2.end(); it++){
		cout << *it << " ";
		solAct.push_back(*it);
	}
	cout << "\n";

	return res;

}


}
#endif