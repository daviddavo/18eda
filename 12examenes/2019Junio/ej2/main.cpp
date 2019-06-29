/*
NOMBRE Y APELLIDOS:

*/


#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;



/* Puedes implementar aquí las funciones auxiliares que consideres
   oportuno */

/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento 

*/
void mejor_renta(Arbin<int> a, bool& es_rentable, int& renta_maxima) {
	/* A IMPLEMENTAR */
	
	
}


Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

void muestra_solucion(bool rentable, int renta_max) {
  if (rentable) {
	 cout << renta_max << endl; 
  }	
  else {
	 cout << "NO_RENTABLE " << endl; 
  }
}

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		bool es_rentable;
		int renta_maxima;
		mejor_renta(a,es_rentable,renta_maxima);
		muestra_solucion(es_rentable,renta_maxima);
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}