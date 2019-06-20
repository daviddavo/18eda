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

    unsigned indRadial() {
        return 0;
    }
};

#endif // _diff_06_h_