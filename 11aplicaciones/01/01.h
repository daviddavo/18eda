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

        auto it1 = _dicc.cbegin(), it2 = other._dicc.cbegin();
        while (it1 != _dicc.cend() && it2 != other._dicc.cbegin() ) {
            if (it1.clave() == it2.clave()) ret.ponValor(it1.clave(), it1.valor()*it2.valor());
        }

        return ret;
    }

    bool operator==(const BigVector & other) const {
        return _dicc == other._dicc;
    }
};