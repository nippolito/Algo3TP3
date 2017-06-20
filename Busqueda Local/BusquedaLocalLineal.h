#ifndef BUSQUEDA_LOCAL_LINEAL_H
#define BUSQUEDA_LOCAL_LINEAL_H

#include <iostream>
#include <set>
#include <utility> 

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

int BusquedaLocalLineal(set<int> matrix [], set<int>& solAct, int n , int m){

	bool noEncontrePozo = true;

	while(noEncontrePozo){
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

	return  CalcularFronteras(matrix, solAct);
}
}
#endif