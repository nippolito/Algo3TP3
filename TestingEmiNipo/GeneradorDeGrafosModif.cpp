#include <iostream>

using namespace std;

void genGrafo(int c, int n, double densidad){
	srand (time(NULL));	 

	//cout << "Ingresar tamaño de clique que se quiere tener: " ES C;
	//cout << "\nIngresar cantidad de nodos total del grafo :" ES N;
	//cout << "\n Ingresar densidad, entre 0 y 1 (Densidad del gafo en realcion a los ejes que no estan en la clique): ES DENSIDAD ";
	bool matrix [n][n];
	for(int i = 0; i < n; i ++){
		for(int j = 0 ; j < n; j++) matrix [i][j] = false;
	}

	int cantAristasEnClique = c*(c-1)/2;
	int cantAristasDisponibles = (n*(n-1)/2) - cantAristasEnClique;
	//cout << "cantAristasDisponibles : "<< cantAristasDisponibles << endl;
	int m = ((densidad) *cantAristasDisponibles )  / 2;

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
	cout << "\n\n"<<endl;
		



}
