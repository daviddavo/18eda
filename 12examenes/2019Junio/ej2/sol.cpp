#include "sol.h"
#include "Arbin.h"

/*
	En el peor de los casos, todos las hojas del arbol son rentables, y, como necesitamos conocer el máximo,
	tendremos que recorrer todos los antecesores de dichas hojas. En resumen, tendríamos una complejidad O(n)
*/
void mejor_renta(const Arbin<int> a, bool& es_rentable, int& renta_maxima, int rentaPrev) {
	int rentaNodo = rentaPrev + a.raiz();
	if (rentaNodo > 0) {
		if (!a.hijoIz().esVacio()) mejor_renta(a.hijoIz(), es_rentable, renta_maxima, rentaNodo);
		if (!a.hijoDer().esVacio()) mejor_renta(a.hijoDer(), es_rentable, renta_maxima, rentaNodo);

		if (a.hijoIz().esVacio() && a.hijoDer().esVacio() && rentaNodo > 0) {
			es_rentable = true;
			if (rentaNodo > renta_maxima) renta_maxima = rentaNodo;
		}
	}
}

void mejor_renta(const Arbin<int> a, bool& es_rentable, int& renta_maxima) {
	es_rentable = false;
	renta_maxima = 0;
	if (a.esVacio()) return;
	
	mejor_renta(a, es_rentable, renta_maxima, 0);
}
