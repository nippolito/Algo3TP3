#include <iostream>
#include <set>
#include <utility> 
#include "../../Busqueda\ Local/BusquedaLocalLineal.h"
#include "../../Busqueda\ Local/BusquedaLocalCuadratica.h"

using namespace std;

void mostrarSet(set<int> & s){
	cout << "[" ;
	for(set<int>::iterator it = s.begin(); it != s.end(); it++){
		cout << *it+1 <<", ";
	}
	cout << "]"<< endl;
}

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
	set<int> s;
	int sizeSA; cin >> sizeSA;
	for(int i = 0 ; i < sizeSA ; i++){
		int aux ; cin >> aux;
		s.insert(aux-1);
	}
	set<int> solAct1 ;
	for(set<int>::iterator it = s.begin(); it != s.end(); it++){
		solAct1.insert(*it);
	}

	set<int> solAct2 ;
	for(set<int>::iterator it = s.begin(); it != s.end(); it++){
		solAct2.insert(*it);
	}


	int resLocal = lineal::BusquedaLocalLineal(matrix, solAct1, n, m);
	int resCuadratica = cuadratico::BusquedaLocalCuadratica(matrix, solAct2, n, m);

	cout << "La respuesta de busqueda local lineal es :" << resLocal << endl;
	mostrarSet(solAct1);

	cout << "\nLa respuesta de busqueda local cuadratica es: " << resCuadratica << endl;
	mostrarSet(solAct2);

	
	return 0 ;	
}