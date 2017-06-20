#include <iostream>

using namespace std;

void densAristasMitad(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	for(int i = 5; i < 601; i++){
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				cout << 4;
				cout << i;
				cout << 0.5;
			}else{
				cout << 10;
				cout << i;
				cout << 0.5;
			}
		}
	}	
}

void densGrafComp(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	for(int i = 5; i < 601; i++){
		for(int j = 0; j < 40; j++){
			cout << 4;
			cout << i;
			cout << 1;
		}
	}	
}

void densPocasArist(){		// hay una clique fija de 10 (excepto hasta menores a 20 que es de 4)
	for(int i = 5; i < 601; i++){
		for(int j = 0; j < 40; j++){
			if(i <= 20){
				cout << 4;
				cout << i;
				cout << 0.1;
			}else{
				cout << 10;
				cout << i;
				cout << 0.1;
			}
		}
	}	
}

int main(){
	// densAristasMitad();
	// densGrafComp();
	// densPocasArist();

	return 0;
}