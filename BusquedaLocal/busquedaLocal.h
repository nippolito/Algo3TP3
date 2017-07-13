#ifndef BUSQUEDA_LOCAL_CUADRATICA_H
#define BUSQUEDA_LOCAL_CUADRATICA_H

#include <iostream>
#include <set>
#include <utility> 
#include "../HeurNipoListaAdy/Grafo.h"

using namespace std;

void mostrarSet(set<int> & s){
	cout << "[" ;
	for(set<int>::iterator it = s.begin(); it != s.end(); it++){
		cout << *it <<", ";
	}
	cout << "]"<< endl;
}

int CalcularFronteras(set<int> matrix [], set<int>& solucion){
	int res = 0 ;
	int tamClique = solucion.size();
	
	for(set<int>::iterator itSol = solucion.begin(); itSol != solucion.end(); itSol ++ ){
		res += cantFronterasQueAporta(tamClique, matrix[*itSol].size() );
	}

	return res;
}

int BusquedaLocalCuadratica(set<int> matrix [], set<int>& solAct, int n , int m){

	bool noEncontrePozo = true;
	set<int> NodosRestantes;
	for(int i = 0; i < n; i ++){
		if(solAct.find(n) == solAct.end()) NodosRestantes.insert(i);
	}
	while(noEncontrePozo){
		mostrarSet(solAct);
		set<int> solucionesSumandoNodo;
		set<int> solucionesRestandoNodo; 
		set<pair<int,int> > solucionesAgregarYRestar;		 // first -> nodo a eliminar ; second -> nodo a agregar				
		
		pair<int, int> NodoQueMaximizaAgregarUnNodo = pair<int,int>(-1,-1);
		pair<int, int> NodoQueMaximizaSacarUnNodo = pair<int,int>(-1,-1);
		pair<pair<int,int>,int> NodosQueMaximizanRestarYSumar = pair<pair<int,int>,int> (pair<int,int>(-1,-1), -1);
		int solucionTalcualEstaba ;

		// guardo primer las soluciones que surgen de agregarle un nodo
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

		// guardo las soluciones que surgen al restar y agregar un nodo
		for(set<int>::iterator it = solAct.begin(); it!= solAct.end(); it++){ // it va a ser mi nodo por eliminar
			for(set<int>::iterator it2 = NodosRestantes.begin() ; it2 != NodosRestantes.end(); it2++){ // it2 va a ser mi nodo nuevo por agregar
				bool esVecinoDeTodos = true;
				for(set<int>::iterator it3 = solAct.begin(); it3 != solAct.end(); it3++){ 
					if(*it3 != *it){ // si estoy en la iteracion que elimino it no me impora que sean vecinos.
						if(matrix[*it2].find(*it3) == matrix[*it2].end()) esVecinoDeTodos = false; // si no son vecinos chau ameo
					}
				}

				if(esVecinoDeTodos){
					solucionesAgregarYRestar.insert(pair<int,int> (*it, *it2));
				}
			}
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
		
		//me fijo la mejor solucion en agregar y sacar
		for(set<pair<int,int> >::iterator it = solucionesAgregarYRestar.begin(); it != solucionesAgregarYRestar.end() ; it++){
			solAct.erase((*it).first);
			solAct.insert((*it).second);
			int aux = CalcularFronteras(matrix, solAct);
			if(aux > NodosQueMaximizanRestarYSumar.second){
				NodosQueMaximizanRestarYSumar.first = *it;
				NodosQueMaximizanRestarYSumar.second = aux;
			} 
			solAct.erase((*it).second);
			solAct.insert((*it).first);
		}

		if(solucionTalcualEstaba >= NodoQueMaximizaSacarUnNodo.second && solucionTalcualEstaba >= NodoQueMaximizaAgregarUnNodo.second && solucionTalcualEstaba >= NodosQueMaximizanRestarYSumar.second)
			noEncontrePozo = false; // encontre pozo
		else if(NodosQueMaximizanRestarYSumar.second >= NodoQueMaximizaAgregarUnNodo.second && NodosQueMaximizanRestarYSumar.second >= NodoQueMaximizaSacarUnNodo.second){ // me conviene restar y sumar
			solAct.erase(NodosQueMaximizanRestarYSumar.first.first);
			solAct.insert(NodosQueMaximizanRestarYSumar.first.second);
		}
		else if( NodoQueMaximizaAgregarUnNodo.second >= NodoQueMaximizaSacarUnNodo.second){ // me conviene sumar un nodo
			solAct.insert(NodoQueMaximizaAgregarUnNodo.first);
		}
		else{// me conviene restar un nodo
			solAct.erase(NodoQueMaximizaSacarUnNodo.first);
		}
	}

	return  CalcularFronteras(matrix, solAct);

}


int BusquedaLocalLineal(set<int> matrix [], set<int>& solAct, int n , int m){

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

	return  CalcularFronteras(matrix, solAct);
}


void HeurGregoLineal (Graph* g, vector <int> solAct){
	int n = g->listaAdy.size();
	
	set<int> matrix [n];
	
	for(int i = 0; i < n; i++ ){
		int m = g->listaAdy[i].size();
		for(int j = 0 ; j < m ; j++){
			matrix[i].insert(g->listaAdy[i][j]);
		}
	}
	
	set<int> sol;
	int n2 = solAct.size();
	for(int i =0 ; i< n2; i ++){
		sol.insert(solAct[i]);
	}
	
	BusquedaLocalLineal(matrix, sol, g->listaAdy.size(), 10 );
	
	for(int i = 0 ; i < n; i ++){
		g->listaAdy[i].clear();
	}
	for(int i= 0 ; i<  n; i ++){
		for(set<int>::iterator it = matrix[i].begin(); it != matrix[i].end(); it++){
			g->listaAdy[i].push_back(*it);
		}
	}
	
	solAct.clear();
	for(set<int>::iterator it = sol.begin(); it != sol.end(); it++){
		solAct.push_back(*it);
	}
}

void HeurGregoCuadratica (Graph* g, vector <int> solAct){
	int n = g->listaAdy.size();
	
	set<int> matrix [n];
	
	for(int i = 0; i < n; i++ ){
		int m = g->listaAdy[i].size();
		for(int j = 0 ; j < m ; j++){
			matrix[i].insert(g->listaAdy[i][j]);
		}
	}
	
	set<int> sol;
	int n2 = solAct.size();
	for(int i =0 ; i< n2; i ++){
		sol.insert(solAct[i]);
	}
	
	BusquedaLocalCuadratica(matrix, sol, g->listaAdy.size(), 10 );
	
	for(int i = 0 ; i < n; i ++){
		g->listaAdy[i].clear();
	}
	for(int i= 0 ; i<  n; i ++){
		for(set<int>::iterator it = matrix[i].begin(); it != matrix[i].end(); it++){
			g->listaAdy[i].push_back(*it);
		}
	}
	
	solAct.clear();
	for(set<int>::iterator it = sol.begin(); it != sol.end(); it++){
		solAct.push_back(*it);
	}
}




#endif
