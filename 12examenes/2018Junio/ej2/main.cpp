#include "sol.h"
#include <string>

using namespace std;

void escribe_arbol(Arbin<char> a) {
	if (a.esVacio()) cout << "#";
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) cout << "[" << a.raiz() << "]";
	else {
		cout << "("; 
		escribe_arbol(a.hijoIz()); 
		cout << a.raiz(); 
		escribe_arbol(a.hijoDer());
		cout << ")";
	}
}


int main() {
	Arbin<char> arbol;
	while (cin.peek() != EOF)  {
		Arbin<char> mapa = lee_arbol(cin);
		cout << "num_a_salvo ";
		escribe_arbol(mapa);
		cout << " => ";
		cout << num_a_salvo(mapa);
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
