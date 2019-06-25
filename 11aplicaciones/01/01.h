#pragma once

#include "DiccionarioHash.h"

class BigVector {
    DiccionarioHash<unsigned long, double> _dicc;

    public:
    BigVector() : _dicc() {}

    void ponValor(unsigned long i, double val) {
        if (val == 0) _dicc.borra(i);
        else _dicc.inserta(i, val);
    }

    double valorDe(unsigned long i) {
        if (!_dicc.contiene(i)) return 0;
        return _dicc.valorPara(i);
    }

    BigVector productoEscalar(const BigVector & other) const {
        BigVector ret = BigVector();

        for (auto it = _dicc.cbegin(); it != _dicc.cend(); it.next()) {

        }

        return ret;
    }
};