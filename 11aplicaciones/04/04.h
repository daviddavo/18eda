#pragma once

#include <string>
#include "DiccionarioHash.h"

typedef std::string tRio;
typedef std::string tPantano;

class Cuenca {
    protected:
    class Pantano {
        public:
        int capacidad;
        int carga;
        Pantano(int n1, int n2) : capacidad(n1), carga(std::min(n1, n2)) {}
    };

    class Rio {
        public:
        int total_litros;
        DiccionarioHash<tPantano, Pantano> pantanos;
        Rio() : total_litros(0) {}
    };

    DiccionarioHash<tRio, Rio> rios;

    public:

    /** Creación de una cuenca hidrográfica vacías */
    Cuenca() {

    }

    /**
     * Añade un río. La cuenca no puede tener dos ríos que se llamen igual. Operación
     * no definida si ya existe el río r en la cuenca.
     */
    void insertar_rio(const tRio & rio) {
        if (!rios.contiene(rio)) rios.inserta(rio, Rio());
    }

    /** 
     * Añade un pantano al río r, con nombre p (un río no puede tener dos pantanos)
     * que se llamen igual). La capacidad máxima del pantano es de n1 hm3. Además,
     * lo llena con n2 hm. Si n2 > n1 entonces lo llena completamente. Operación
     * no definida si ya existe algún pantano de nombbre p en el rio r o no existe el rio
     * r.
     */
    void insertar_pantano(const tRio & rio, const tPantano & pantano, int n1, int n2) {
        auto it = rios.busca(rio);
        if (it != rios.end()) {    // Hemos encontrado el rio
            it.valor().pantanos.inserta(pantano, Pantano(n1, n2));
            it.valor().total_litros += std::min(n1, n2);
        }
    }
    void embalsar(const tRio & rio, const tPantano & pantano, int n);

    /**
     * Devuelve la cantidad de agua embalsada en el pantano p del río r. Operación
     * no definida si el río o el pantano no existen
     */
    unsigned int embalsado_pantano(const tRio & rio, const tPantano & pantano) const {
        auto rit = rios.cbusca(rio);
        if (rit != rios.cend()) {
            auto pit = rit.valor().pantanos.cbusca(pantano);
            if (pit != rit.valor().pantanos.cend())
                return pit.valor().carga;
        }

        return 0;
    }
    unsigned int embalsado_cuenca(const tRio & rio);
    void transvasar(const tRio & rio1, const tPantano & pantano1, const tRio & rio2, const tPantano & pantano2, int n);
    private:
    // Aquí toda la mierda que quieras usar para implementar el TAD
};