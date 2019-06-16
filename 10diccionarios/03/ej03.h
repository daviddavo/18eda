#ifndef dict_ej03_h_
#define dict_ej03_h_

#include "../arbol_busqueda/diccionario.h"

namespace ej03 {
    template <class tClave, class tValor>
    class DiccionarioMejorado : public Diccionario<tClave, tValor> {
        public:
        DiccionarioMejorado(const Diccionario<tClave, tValor> & d) : Diccionario<tClave, tValor>(d) {};

        tClave consultaK(int k) {
            if (k < 0) throw EAccesoNoValido();

            int i = 0;
            typename Diccionario<tClave,tValor>::ConstIterator it = this->cbegin();
            while(it != this->cend() && i < k) {
                it.next(); 
                ++i;
            }

            if (i > k) throw EAccesoNoValido();

            return it.clave();
        }
    };
}

#endif