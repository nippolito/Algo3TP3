#include <iostream>

#define CANT_NODOS 300


using namespace std;

void densAristasMitad(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	for(int i = 5; i < CANT_NODOS; i++){
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				cout << 4<<" ";
				cout << i<<" ";
				cout << 0.5<< endl;
			}else{
				cout <<10<<" ";
				cout << i<<" ";
				cout << 0.5<< endl;
			}
		}
	}	
}

void densGrafComp(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	for(int i = 5; i < CANT_NODOS; i++){
		for(int j = 0; j < 40; j++){
			cout << 4<<" ";
			cout << i<<" ";
			cout << 1<< endl;
		}
	}	
}

void densPocasArist(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	for(int i = 5; i < CANT_NODOS; i++){
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				cout << 4<<" ";
				cout << i<<" ";
				cout << 0.1<< endl;
			}else{
				cout << 10<<" ";
				cout << i<<" ";
				cout << 0.1 << endl;
			}
		}
	}	
}

int main(){
	densAristasMitad();
	// densGrafComp();
	// densPocasArist();
	cout << -1;
	return 0;
}