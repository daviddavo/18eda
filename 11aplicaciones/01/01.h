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

    double valorDe(unsigned long i) const {
        if (!_dicc.contiene(i)) return 0;
        return _dicc.valorPara(i);
    }

    // Con una buena función hash, la complejidad de esta función es de n,
    // de ser mala, la complejidad puede ser n^2 en el peor de los casos
    BigVector productoEscalar(const BigVector & other) const {
        BigVector ret = BigVector();

        auto it1 = _dicc.cbegin();
        while (it1 != _dicc.cend()) {
            ret.ponValor(it1.clave(), it1.valor() * other.valorDe(it1.clave()));
            it1.next();
        }

        return ret;
    }

    BigVector suma(const BigVector & other) const {
        BigVector ret = BigVector(other);

        auto it1 = _dicc.cbegin();
        while (it1 != _dicc.cend()) {
            ret.ponValor(it1.clave(), ret.valorDe(it1.clave()) + it1.valor());
            it1.next();
        }

        return ret;
    }

    bool operator==(const BigVector & other) const {
        return _dicc == other._dicc;
    }

    bool operator!=(const BigVector & other) const {
        return _dicc != other._dicc;
    }
};