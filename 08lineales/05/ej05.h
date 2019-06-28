#pragma once

#include "pila.h"

namespace ej05 {

    template <typename T>
    void imprimeRecursivo(ostream & out, Pila<T> & pila) {
        if (pila.esVacia()) return;

        T prevCima = pila.cima();
        pila.desapila();
        imprimeRecursivo(out, pila);
        out << prevCima << '\n';
    }

    template <typename T>
    void imprimeIterativo(ostream & out, Pila<T> & pila) {
        Pila<T> aux;

        while(!pila.esVacia()) {
            aux.apila(pila.cima());
            pila.desapila();
        }

        while(!aux.esVacia()) {
            out << aux.cima() << '\n';
            aux.desapila();
        }
    }
}