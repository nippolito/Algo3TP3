#include <iostream>
#include <stdlib.h>
#include <set>
#include <map>
#include <utility>
#include <stdio.h>

using namespace std;

bool EstanDefinidos(set<int> set[], int c1, int c2){
	return (set[c1].find(c2) != set[c1].end());
}

int main(){
	
	srand (time(NULL));	 
	while(true){

	//cout << "Ingresar tamaño de clique que se quiere tener: ";
	int c ;  cin >> c ;
	if(c == -1) return 0 ;
	//cout << "\nIngresar cantidad de nodos total del grafo :";
	int n ; cin >> n;
	double densidad = 0; 
	//cout << "\n Ingresar densidad, entre 0 y 1 (Densidad del gafo en realcion a los ejes que no estan en la clique): ";
	cin >> densidad;
	
	bool matrix [n][n];
	for(int i = 0; i < n; i ++){
		for(int j = 0 ; j < n; j++) matrix [i][j] = false;
	}

	int cantAristasEnClique = c*(c-1)/2;
	int cantAristasDisponibles = (n*(n-1)/2) - cantAristasEnClique;
	//cout << "cantAristasDisponibles : "<< cantAristasDisponibles << endl;
	int m = (densidad) *cantAristasDisponibles;

	cout << n <<" "<< m+cantAristasEnClique  << endl;

	for(int i = 0; i < c ; i ++ ){
		for(int j = i+1; j < c; j++){
			matrix[i][j] = true;
			matrix[j][i] = true;
			
			cout << i+1 << " " << j+1 <<endl;
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
		
		cout << c1+1 << " " << c2+1  << endl;


	}
	cout << "\n"<<endl;
	}	

	return 0 ;
}