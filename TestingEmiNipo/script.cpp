#include <iostream>	
#include "GeneradorDeGrafosModif.cpp"
using namespace std;

/*

NOTA IMPORTANTE:
Para correr los tests y ponerlos en un txt, compilar, y con el objeto desde consola ejecutar:
./<script.o> &> <tuvieja.csv>

*/

// preguntarle a Emi como correr exactamente

void densAristasMitad(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	int c; //Tamaño de la clique 
	int n; //Tamaño del grafo
	int d; //Tamaño de la densidad

	for(int i = 300; i < 301; i++){ //601
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				c = 4;
				n = i;
				d = 0.5;
				genGrafo(c, n, d);

			}else{
				c = 10;
				n = i;
				d = 0.5;
				genGrafo(c, n, d);
			}
		}
	}
	cout << -1 << endl;	//Para saber donde terminar de levantar el txt
}

void densGrafComp(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	int c; //Tamaño de la clique 
	int n; //Tamaño del grafo
	int d; //Tamaño de la densidad

	for(int i = 5; i < 50; i++){ //era 601
		for(int j = 0; j < 40; j++){
			c = 4;
			n = i;
			d = 1;
			genGrafo(c, n, d);
		}
	}

	cout << -1 << endl;	//Para saber donde terminar de levantar el txt
}

void densPocasArist(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	int c; //Tamaño de la clique 
	int n; //Tamaño del grafo
	int d; //Tamaño de la densidad

	for(int i = 5; i < 51; i++){//eran 601
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				c = 4;
				n = i;
				d = 0.1;
				genGrafo(c, n, d);
			}else{
				c = 10;
				n = i;
				d = 0.1;
				genGrafo(c, n, d);
			}
		}
	}

	cout << -1 << endl;	//Para saber donde terminar de levantar el txt
}

int main(){
	densAristasMitad();
	//densGrafComp();
	//densPocasArist();

	return 0;
}