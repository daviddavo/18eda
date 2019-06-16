#ifndef balancear_h_
#define balancear_h_
#include "../arbol_busqueda/diccionario.h"
#include "lista.h"

/** 1. Implementa una operación en lo árboles de búsqueda que balancee el árbol.
 * Se permite el uso de estructuras de datos auxiliares
 */
namespace ej01 {
    class DiccionarioMejorado : public Diccionario<int, int> {
        public:
        void balancear() {
            Lista<Nodo> inorden = Lista<Nodo>();

            for (ConstIterator it = cbegin(); it != cend(); it.next()) {
                inorden.pon_final(it.clave());
            }

            _ra = balancearAux(inorden, 0, inorden.longitud());
        }

        protected:
        Nodo* balancearAux(Lista<Nodo> & nodos, int inicio, int final) {
            if (final <= inicio) return NULL;

            int m = (inicio + final)/2;
            Nodo * ra = nodos.

            return ra;
        }
    };
}

class TestDiccionarios01 : public :: TestDiccionarios {
    protected:
        /**
         *       30
         *      /
         *     /
         *    20
         *   /
         *  /
         * 10
         */
        DiccionarioMejorado<int> d0;
        void SetUp() override {
            Diccionario<int>::Nodo n0 = Diccionario<int>::Nodo(

            );
        }
};

TEST_F(TestDiccionarios01, balanceo) {

}

#endif