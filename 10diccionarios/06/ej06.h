#ifndef _dicc_06_h_
#define _diff_06_h_

#include "hash.h"
#include "DiccionarioHash.h"

/**
 * Se define el índice radial de una tabla abierta como la longitud del vector
 * por el número de elementos de la lista de colisión más larga. Extiende el
 * TAD diccionario basado en tablas abiertas con un método que devuelva su índice
 * radial
 */

template <class tClave, class tValor>
class DiccionarioRadial : public DiccionarioHash<tClave, tValor> {
    public:
    DiccionarioRadial(const DiccionarioHash<tClave, tValor> & dic) : DiccionarioHash<tClave, tValor>(dic) {
        _tamColisiones = new unsigned [this->_tabla._tam];
        for (int i = 0; i < this->_tabla._tam; ++i)
            _tamColisiones[i] = 0;
    }

    /**
     * Longitud del vector * numero de elementos de la lista de colisión más larga
     */
    unsigned indRadial() {
        unsigned maxColisiones;
        for (int i = 0; i < this->_tabla._tam; ++i)
            if (_tamColisiones[i] > maxColisiones)
                maxColisiones = _tamColisiones[i];
        
        return this->_tabla._tam * maxColisiones;
    }

    ~DiccionarioRadial() {
        delete [] _tamColisiones;
    }

    private:
    unsigned * _tamColisiones;

    static void borraAux(Tabla & tabla, const tClave & clave) override {
        DiccionarioHash<tClave,tValor>::borraAux(tabla, clave);
        unsigned int ind = ::h(clave) % tabla._tam;
        _tamColisiones[ind]--;
    }

    static void insertaAux(Tabla & tabla, const tClave & clave, const tValor & valor) override {
        DiccionarioHash<tClave,tValor>::insertaAux()
    }
};

#endif // _diff_06_h_