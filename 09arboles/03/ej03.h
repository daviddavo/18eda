#ifndef __EJ03
#define __EJ03

#include <iostream>
#include "../02/ej02.h"

/**
3.  Implementa una función recursiva template <class T> void printArbol(const Arbin<T> &arbol);
    que escriba por pantalla el arbol que recibe por parametro, segun las siguientes reglas:
    -   Si el arbol es vacio, escribira <vacio> y despues retorno de carro
    -   Si el arbol es un arbol hoja, escribira el contenido de la raiz y un retorno de carro
    -   Si el arbol tiene algun hijo, escribira el contenido del nodo raiz, y recursivamente en 
        las siguientes lineas el hijo izquierdo y despues el hijo derecho. Los hijos izquierdo y derecho están
        tabulados, dejando tres espacios
*/
namespace ej03 {
    template <class T> 
    void printArbol(const Arbin<T> &arbol, ostream& stream, unsigned k = 0) {
        for (int i = 0; i < k*3; ++i) stream << ' ';

        if (arbol.esVacio()) {
            stream << "<vacio>" << endl;
        } else {
            stream << arbol.raiz() << endl;
            if (!ej02::esHoja(arbol)) {
                printArbol(arbol.hijoIz(), stream, k+1);
                printArbol(arbol.hijoDer(), stream, k+1);
            }
        }
    }

    template <class T> 
    void printArbol(const Arbin<T> &arbol) {
        printArbol(arbol, cout);
    }
}

#endif