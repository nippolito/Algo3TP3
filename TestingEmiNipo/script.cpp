#include <iostream>
#include "GeneradorDeGrafosModif.cpp"
using namespace std;

/*

NOTA IMPORTANTE:
Para correr los tests y ponerlos en un txt, compilar, y con el objeto desde consola ejecutar:
./<script.o> &> <tuvieja.txt>

*/
void densAristasMitad(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	int c; //Tamaño de la clique 
	int n; //Tamaño del grafo
	int d; //Tamaño de la densidad

	for(int i = 5; i < 601; i++){ //601
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				c = 4;
				n = i;
				d = 0.5;
				genGrafoEmi(c, n, d);

			}else{
				c = 10;
				n = i;
				d = 0.5;
				genGrafoEmi(c, n, d);
			}
		}
	}
	cout << -1 << endl;	//Para saber donde terminar de levantar el txt
}

void densGrafComp(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	int c; //Tamaño de la clique 
	int n; //Tamaño del grafo
	int d; //Tamaño de la densidad

	for(int i = 5; i < 50; i++){ //era 600
		for(int j = 0; j < 40; j++){
			c = 4;
			n = i;
			d = 1;
			genGrafoEmi(c, n, d);
		}
	}

	cout << -1 << endl;	//Para saber donde terminar de levantar el txt
}

void densPocasArist(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	int c; //Tamaño de la clique 
	int n; //Tamaño del grafo
	int d; //Tamaño de la densidad

	for(int i = 5; i < 601; i++){
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				c = 4;
				n = i;
				d = 0.1;
				genGrafoEmi(c, n, d);
			}else{
				c = 10;
				n = i;
				d = 0.1;
				genGrafoEmi(c, n, d);
			}
		}
	}

	cout << -1 << endl;	//Para saber donde terminar de levantar el txt
}

int main(){
	//densAristasMitad();
	// densGrafComp();
	//densPocasArist();

	return 0;
}