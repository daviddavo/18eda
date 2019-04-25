#ifndef __EJ01_h
#define __EJ01_h

#include "arbin.h"

/**
1. Extiende la implementación de los arboles binarios con las siguientes operaciones
    - numNodos: devuelve el numero de nodos del arbol
    - esHoja: devuelve cierto si el arbol es una hoja (los hijos izquierdo y derecho son vacios)
    - numHojas: devuelve el numero de hojas del arbol
    - talla: devuelve la talla del arbol
    - frontera: devuelve una lista con todas las hojas del arbol de izquierda a derecha
    - espejo: devuelve un arbol nuevo que es la imagen especular del original
    - minElem: devuelve el elemento mas pequeño de todos los almacenados en el arbol. 
        Es un error ejecutar esta operacion sobre una arbol vacio
*/

namespace ej01 {
    template <class T>
    class ArbinMejorado : public Arbin<T> {
    public:
        ArbinMejorado(const Arbin<T>& a) : Arbin<T>(a) {};

        const unsigned numNodos() {
            return numNodos(this->_ra);
        }

        const bool esHoja() {
            if (this->esVacio()) throw EArbolVacio();
            return esHoja(this->_ra);
        }

        const unsigned numHojas() {
            return numHojas(this->_ra);
        }

        const unsigned talla() {
            return talla(this->_ra);
        }

        ArbinMejorado<T> espejo() {
            typename Arbin<T>::Nodo * aux = this->_ra;
            espejo(aux);
            return Arbin<T>(aux);
        }

        const T minElem() {
            return minElem(this->_ra);
        }
    protected:
        const unsigned numNodos(const typename Arbin<T>::Nodo * ra) {
            if (ra == NULL) return 0;

            return 1 + numNodos(ra->_iz) + numNodos(ra->_dr);
        }

        const bool esHoja(const typename Arbin<T>::Nodo * ra) {
            return ra->_iz == NULL && ra->_dr == NULL;
        }

        const unsigned numHojas(const typename Arbin<T>::Nodo * ra) {
            if (ra == NULL) return 0;
            if (esHoja(ra)) return 1;
            return numHojas(ra->_iz) + numHojas(ra->_dr);
        }

        const unsigned talla(const typename Arbin<T>::Nodo * ra) {
            if (ra == NULL) return 0;
            if (esHoja(ra)) return 1;
            return 1 + max(talla(ra->_iz), talla(ra->_dr));
        }

        void espejo(const typename Arbin<T>::Nodo * ra) {
            if (ra == NULL) throw EArbolVacio();
            
        }

        const T minElem(const typename Arbin<T>::Nodo * ra) {
            if (ra == NULL) throw EArbolVacio();
            if (esHoja(ra)) return ra->_elem;
            else return min(ra->_elem, min(minElem(ra->_iz), minElem(ra->_dr)));
        }
    };
}

#endif