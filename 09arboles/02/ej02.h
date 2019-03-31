#ifndef __EJ02
#define __EJ02
#include "arbin.h"

namespace ej02 {
	template <class T>
	unsigned numNodos (const Arbin<T> & arb) {
        if (arb.esVacio()) return 0;
        else return 1 + numNodos(arb.hijoIz()) + numNodos(arb.hijoDer());
	}

    template <class T>
    bool esHoja (const Arbin<T> & arb) {
        if (arb.esVacio()) throw EArbolVacio();
        return arb.hijoIz().esVacio() && arb.hijoDer().esVacio();
    }

    template <class T>
    unsigned numHojas (const Arbin<T> & arb) {
        if (esHoja(arb)) return 1;
        else return numHojas(arb.hijoIz()) + numHojas(arb.hijoDer());
    }

    template <class T>
    unsigned talla(const Arbin<T> & arb) {
        if (esHoja(arb)) return 1;
        else return 1 + max(talla(arb.hijoIz()), talla(arb.hijoDer()));
    }

    template <class T>
    const Arbin<T> espejo(const Arbin<T> & arb) {
        if (esHoja(arb)) return Arbin<T>(arb);

        return Arbin<T>(espejo(arb.hijoDer()), arb.raiz(), espejo(arb.hijoIz()));
    }

    template <class T>
    const T& minElem(const Arbin<T> & arb) {
        if (arb.esVacio()) throw EArbolVacio();
        if (esHoja(arb)) return arb.raiz();
        T minHijos = min(minElem(arb.hijoIz()), minElem(arb.hijoDer()));
        return min(arb.raiz(), minHijos);
    }
}

#endif