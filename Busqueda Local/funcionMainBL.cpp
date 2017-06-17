#include <iostream>
#include <set>
#include <utility> 
#include "BusquedaLocal.h"

int main(){
	int n ; cin >> n;
	int m ; cin >> m;

	set<int> matrix[n];

	//INGRESO LA MATRIZ
	for(int i = 0; i < m ; i ++){
		int n1,n2;
		cin >> n1; cin >> n2;	
		matrix[n1-1].insert(n2-1);
		matrix[n2-1].insert(n1-1);
	}

	//INGRESO LA SEMILLA DONDE EMPEZAR A HACER LA BUSQUEDA LOCAL
	set<int> solAct;
	int sizeSA; cin >> sizeSA;
	for(int i = 0 ; i < sizeSA ; i++){
		int aux ; cin >> aux;
		solAct.insert(aux-1);
	}

	BusquedaLocal(matrix, solAct, n, m);
	
	return 0 ;	
}