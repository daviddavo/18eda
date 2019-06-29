#pragma once

#include "lista.h"

namespace ej30 {
    template <typename T>
    class ListaMejorada : public Lista<T> {
        public:
            ListaMejorada() : Lista<T>() {}
            ListaMejorada(const Lista<T> & lista) : Lista<T>(lista) {}

            /**
             * El mover un elemento al principio tiene coste constante, lo que tiene
             * coste lineal (y hace a este método de complejidad lineal) es la búsqueda
             * del elemento en la posición pos
             * 
             * De tener una implementación con "nodos fantasma" no sería necesario
             * hacer los casos especiales de querer mover _prim/_ult
             */
            void llevarAlPrincipio(unsigned int pos) {
                if (pos < 1 || pos > this->_numElems) throw EAccesoInvalido();
                if (pos == 1) return;

                // Nota: En C++ auto se resuelve en tiempo de compilación,
                // es simplemente un alias a typename Lista<T>::Nodo

                // Buscamos el elemento i-ésimo
                auto * aux = this->_prim;
                if (pos == this->_numElems) {
                    aux = this->_ult;
                } else {
                    for (unsigned i = 1; i < pos; ++i)
                        aux = aux->_sig;
                }

                // Primero vamos a conectar los dos adyacentes al elemento que movemos
                auto * ant = aux->_ant;
                auto * sig = aux->_sig;

                ant->_sig = sig;
                if (aux != this->_ult) sig->_ant = ant; // Caso ult
                else this->_ult = ant;

                // Ahora tenemos que "conectar" el que movemos al previo primero
                aux->_sig = this->_prim;
                this->_prim->_ant = aux;

                // Hacemos que el puntero _prim apunte al nuevo primero
                this->_prim = aux;
                this->_prim->_ant = NULL;
            }

            bool operator==(const ListaMejorada<T> & other) const {
                return (Lista<T>)(*this) == other;
            }

            bool operator!=(const ListaMejorada<T> & other) const {
                return *this != other;
            }
    };
}