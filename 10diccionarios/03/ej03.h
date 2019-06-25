#ifndef dict_ej03_h_
#define dict_ej03_h_

#include "lista.h"
#include "../arbol_busqueda/diccionario.h"

namespace ej03 {
    template <class tClave, class tValor>
    class DiccionarioMejorado : public Diccionario<tClave, tValor> {
        public:
        DiccionarioMejorado(const Diccionario<tClave, tValor> & d) : Diccionario<tClave, tValor>(d) {};

        /**
         * Recibe un entero k y devuelve la k-esima clave del diccionario (considera que en un diccionario con n
         * elementos las claves se numeran desde k = 0 hasta k = n-1)
         */
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

        /**
         * Recibe dos claves, a y b, y devuelve la lista con los valores asociados que están en el intervalo
         */
        Lista<tValor> recorreRango(const tClave & a, const tClave & b) {
            if (a > b) throw EClaveErronea();

            Lista<tValor> ret = Lista<tValor>();

            auto it = this->cbegin();
            for (; it != this->cend() && it.clave() != a ; it.next());
            for (; it != this->cend() && it.clave() != b; it.next()) ret.pon_final(it.clave());
            if (it == this->cend()) throw EClaveErronea();
            
            ret.pon_final(it.clave());

            return ret;
        }

        /**
         * Recibe un iterador no constante, elimina el elemento apuntado por él y devuelve un iterador al siguiente
         * elemento del diccionario
         */
        typename Diccionario<tClave, tValor>::Iterator erase(const typename Diccionario<tClave, tValor>::Iterator & it) {
            if (it == this->end()) throw EAccesoInvalido();

            this->borra(it.clave());
            return this->busca(it.clave());
        }
    };
}

#endif