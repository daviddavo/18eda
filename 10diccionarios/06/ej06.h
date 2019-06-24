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
    DiccionarioRadial(const DiccionarioHash<tClave, tValor> & dic) : DiccionarioHash<tClave, tValor>(dic) {}

    /**
     * Longitud del vector * numero de elementos de la lista de colisión más larga
     */
    unsigned indRadial() {
        unsigned col, maxColisiones = 0;
        for (unsigned i = 0; i < this->_tabla._tam; ++i) {
            
            col = calcularColisiones(this->_tabla, i);
            if (col > maxColisiones)
                maxColisiones = col;
        }
        
        return this->_tabla._tam * maxColisiones;
    }

    protected:
    static unsigned calcularColisiones(const typename DiccionarioHash<tClave,tValor>::Tabla & tabla, int index) {
        typename DiccionarioHash<tClave,tValor>::Nodo * nodo = tabla._v[index];
        unsigned cnt = 0;
        for (; nodo != NULL; nodo = nodo->_sig)
            ++cnt;

        return cnt;
    }
};

#endif // _diff_06_h_