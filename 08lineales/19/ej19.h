#pragma once

#include "lista.h"

namespace ej19 {
    template <typename T>
    class ListaMejorada : public Lista<T> {
        public:
        ListaMejorada() : Lista<T>() {}
        ListaMejorada(const Lista<T> & lista) : Lista<T>(lista) {}

        void intercalar() {
            auto * actCabeza = this->_prim;

            while (actCabeza != NULL) {    
                auto * nextUlt = this->_ult->_ant;
                auto * nextCabeza = actCabeza->_sig;

                this->_ult->_sig = actCabeza->_sig;
                actCabeza->_sig->_ant = this->_ult;

                actCabeza->_sig = this->_ult;
                this->_ult->_ant = actCabeza;

                this->_ult = nextUlt;
                actCabeza = nextCabeza;
            }
        }
    };
}