#include "main.h"
#include <string>

using namespace std;
/**
 * EN el desarrollo de un juego de aventuras conversacionales se está
 * representando el mapa del juego mediante un árbol binario de personajes.
 * En cada nodo del árbol hay un personaje (mostruo, caballero o dama) representado
 * a través de un carácter ('M', 'C' y 'D').
 * 
 * Se dice que un nodo está a salvo cuando:
 * i) En él hay una dama
 * ii) El número de monstruos que hay en el camino que va desde la raiz a dicho
 * 	   nodo es menor o igual que hay en los nodos descendientes de dicho nodo
 */

/**
  FUNCION A IMPLEMENTAR.
  Aparte de esta función, puedes implementar todas las funciones auxiliares que
  consideres oportuno. 
  Debes describir y justificar aquí la complejidad de la implementación realizada:
  
  

*/
int num_a_salvo(const Arbin<char>& a, int monstruos, int caballeros) {
	int ret = 0;

	if (a.raiz() == 'M') monstruos += 1;
	int caballerosIzda = 0;
	int caballerosDcha = 0;
	ret += num_a_salvo(a.hijoIz(), monstruos, caballerosIzda);
	ret += num_a_salvo(a.hijoDer(), monstruos, caballerosDcha);

	caballeros = caballerosIzda + caballerosDcha;
	if (a.raiz() == 'C') caballeros += 1;
	else if (a.raiz() == 'D' && caballeros >= monstruos) ret += 1;

	return ret;  
}

int num_a_salvo(const Arbin<char>& a) {
	return num_a_salvo(a, 0, 0);
}



Arbin<char> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
  		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = lee_arbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = lee_arbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}


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
