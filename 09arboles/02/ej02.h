#ifndef __EJ02
#define __EJ02
#include "arbin.h"

namespace ej02 {
	template <class T>
	unsigned numNodos (const Arbin<T> arb) {
        if (arb.esVacio()) return 0;
        else return 1 + numNodos(arb.hijoIz()) + numNodos(arb.hijoDer());
	}

    template <class T>
    bool esHoja (const Arbin<T> arb) {
        return arb.esVacio() || arb.hijoIz().esVacio() && arb.hijoDer().esVacio();
    }

    template <class T>
    unsigned numHojas (const Arbin<T> arb) {
        if (arb.esHoja()) return 1;
        else return numHojas(arb.hijoIz()) + numHojas(arb.hijoDer());
    }

    template <class T>
    unsigned talla(const Arbin<T> arb) {
        if (arb.esHoja()) return 1;
        else return 1 + max(talla(arb.hijoIz()), talla(arb.hijoDer()));
    }
}

#endif