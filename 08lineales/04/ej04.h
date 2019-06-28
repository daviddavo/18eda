#pragma once
#include <string>
#include "pila.h"

using namespace std;

namespace ej04 {
    int posFija(const string & str) {
        Pila<char> pila;

        int res;
        for (int i = 0; i < str.length(); i++) {
            if ('0' <= str[i] && str[i] <= '9') {
                pila.apila(str[i]-'0');
            } else {
                res = pila.cima();
                pila.desapila();

                switch(str[i]) {
                    case '+': res = pila.cima() + res; break;
                    case '-': res = pila.cima() - res; break;
                    case '*': res = pila.cima() * res; break;
                    case '/': res = pila.cima() / res; break;
                }

                pila.desapila();
                pila.apila(res);
            }
        }

        return pila.cima();
    }
}