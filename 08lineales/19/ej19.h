#pragma once

#include "lista.h"

namespace ej19 {
    template <typename T>
    class ListaMejorada : public Lista<T> {
        public:
        ListaMejorada() : Lista<T>() {}
        ListaMejorada(const Lista<T> & lista) : Lista<T>(lista) {}

        void intercalar() {
            if (this->_prim == this->_ult || this->_prim->_sig == this->_ult)
                return;

            auto * actCabeza = this->_prim;
            auto * actUlt = this->_ult;

            while (actCabeza->_sig != this->_ult && actCabeza != this->_ult) {    
                auto * nextUlt = actUlt->_ant;
                auto * nextCabeza = actCabeza->_sig;

                actUlt->_sig = actCabeza->_sig;
                actCabeza->_sig->_ant = actUlt;

                actCabeza->_sig = actUlt;
                actUlt->_ant = actCabeza;

                actUlt = nextUlt;
                actCabeza = nextCabeza;
                this->_ult = actUlt;
                this->_ult->_sig = NULL;
            }
        }
    };
}