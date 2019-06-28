#pragma once

#include "lista.h"

namespace ej18 {
    template<typename T>
    class ListaMejorada : public Lista<T> {
        public:
            ListaMejorada() : Lista<T>() {}
            ListaMejorada(const Lista<T> & lista) : Lista<T>(lista) {}

            void insertarPorPosicion(const T&elem, int pos) {
                if (pos < 0 || pos > this->_numElems) throw EAccesoInvalido();

                if (pos == 0) this->pon_ppio(elem);
                else if (pos == this->_numElems) this->pon_final(elem);
                else {
                    typename Lista<T>::Nodo * n = this->_prim;

                    if (pos <= this->_numElems/2) {
                        int i = 0;
                        while (i < pos-1) {
                            n = n->_sig;
                            ++i;
                        }
                    } else {
                        n = this->_ult;
                        int i = this->_numElems;
                        while (i > pos) {
                            n = n->_ant;
                            --i;
                        }
                    }

                    typename Lista<T>::Nodo * nuevo = new typename Lista<T>::Nodo(n, elem, n->_sig);
                    n->_sig = nuevo;
                    nuevo->_sig->_ant = nuevo;
                }
            }

            bool operator==(const Lista<T> & other) const {
                return (Lista<T>)(*this) == other;
            }

            bool operator!=(const Lista<T> & other) const {
                return !(*this == other);
            }
    };
}