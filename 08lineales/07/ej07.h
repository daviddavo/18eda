#pragma once

#include "cola.h"

namespace ej07 {
    template <typename T>
    void invertir(Pila<T> & pila, int n) {
        Cola<T> aux;
        for (int i = 0; i < n && !pila.esVacia(); ++i) {
            aux.pon(pila.cima());
            pila.desapila();
        }

        while(!aux.esVacia()) {
            pila.apila(aux.primero());
            aux.quita();
        }
    }
}