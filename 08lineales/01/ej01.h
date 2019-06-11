#ifndef __EJ01_h
#define __EJ01_h

#include <iostream>

/** Implementa, con ayuda de una pila, un procedimiento no recursivo que reciba como parámetro un número entero
	n >= 0 y escriba por pantalla sus dígitos en orden lexicográfico y su suma.
	Por ejemplo, ante n = 64323 escribirá */
void ej01(std::ostream & s, int n) {
    Pila<int> pila = Pila<int>();

    while (n > 0) {
        pila.apila(n%10);

        n = n/10;
    }

    int suma = 0;
    while (!pila.esVacia()) {
        suma += pila.cima();
        s << pila.cima();

        pila.desapila();
        
        if (!pila.esVacia())
            s << " + ";
    }

    s << " = " << suma;
}

#endif