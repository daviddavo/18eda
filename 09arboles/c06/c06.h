#ifndef __C06_h
#define __C06_h

#include "arbin.h"

template <typename T>
unsigned int numero_hojas_mas_profundas_que(const Arbin<T>& a, unsigned int k, int dep) {

    if (a.esVacio()) return 0;
    if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {
        if (dep > k) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return (numero_hojas_mas_profundas_que(a.hijoIz(), k, dep + 1) + numero_hojas_mas_profundas_que(a.hijoDer(), k, dep + 1));
    }
}

//-----Función nueva------
template <typename T>
unsigned int numero_hojas_mas_profundas_que(const Arbin<T>& a, unsigned int k) {
    // A IMPLEMENTAR
    return numero_hojas_mas_profundas_que(a, k, 1);
}

#endif