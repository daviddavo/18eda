#ifndef balancear_h_
#define balancear_h_
#include "arbol_busqueda/diccionario.h"
#include "lista.h"

/** 1. Implementa una operación en lo árboles de búsqueda que balancee el árbol.
 * Se permite el uso de estructuras de datos auxiliares
 */
namespace ej01 {
    template <class T>
    class DiccionarioMejorado : public Diccionario<T> {
        public:

        void balancear() {
            Lista<Nodo> inorden = Lista<Nodo>();

            for (ConstIterator it = cbegin(); it != cend(); it.next()) {
                inorden.pon_final(it.elem());
            }

            _ra = balancearAux(inorden, 0, inorden.longitud());
        }

        protected:
        Nodo* balancearAux(Lista<Nodo> & nodos, int inicio, int final) {
            if (final <= inicio) return NULL;

            int m = (inicio + final)/2;
            Node * ra = nodos.

            return ra;
        }
    };
}

#endif