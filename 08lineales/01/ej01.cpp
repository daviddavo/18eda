#include "ej01.h"
#include "pila.h"

void ej01(ostream s, int n) {
	Pila pila = Pila<int>();

	while (n > 0) {
        pila.apila(n%10);

		n = n/10;
	}

    int suma = 0;
    while (!pila.esVacia()) {
        suma += pila.cima();
        s << pila.cima << " + ";
    }
}