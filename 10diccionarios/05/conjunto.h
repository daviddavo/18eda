/** Implementa un TAD conjunto basado en las tablas dispersas con las operaciones
 * habituales: ConjuntoVacio(), inserta(), borra(), esta(), union() [operator+], interseccion() [operator&&]
 * y diferencia() [operator-]
 */
#include "hash.h"

class EYaEnConjunto {};

namespace ej05 {
    template <class T>
    class Conjunto {
    protected:
        class Nodo {
        public:
            /* Constructores. */
            Nodo(const T &elem) : 
            _elem(elem), _sig(NULL) {};
            
            Nodo(const T &elem, Nodo *sig) : 
            _elem(elem), _sig(sig) {};
            
            /* Atributos p�blicos. */
            T _elem;    
            Nodo *_sig;  // Puntero al siguiente nodo.
        };  

        /**
         * Representaci�n de la tabla. La tabla contiene: (i) el array de punteros a nodos,
         * (ii) el tama�o actual, (iii) el n�mero de elementos que aloja
         */
        class Tabla {
        public:
            Nodo **_v;               ///< Array de punteros a Nodo.
            unsigned int _tam;       ///< Tama�o del array _v.
            unsigned int _numElems;  ///< N�mero de elementos en la tabla.   
        };
        
        Tabla _tabla;  //< Tabla dispersa

    public:
        static const int TAM_INICIAL = 8;

        Conjunto(unsigned n) {
            _tabla._v = new Nodo*[n];
            _tabla._tam = n;
            _tabla._numElems = 0;

            for (unsigned i = 0; i < _tabla._tam; ++i)
                _tabla._v[i] = nullptr; // Debugging
        }

        Conjunto(const Conjunto<T> & conj) : Conjunto(conj._tabla._tam) {
            for (ConstIterator it = conj.cbegin(); it != conj.cend(); it.next())
                insertaAux(_tabla, it.elem());
        }

        Conjunto() : Conjunto(TAM_INICIAL) {}

        ~Conjunto() {
            libera(_tabla);
        }

        const bool esta(const T &elem) const {
            // Obtenemos el índice asociado a esa clave
            unsigned int ind = ::h(elem) % _tabla._tam;

            // Buscamos un nodo que contenga esa clave
            Nodo * nodo = buscaNodo(elem, _tabla._v[ind]);
            return nodo != NULL;
        }

        void inserta(const T &elem) {
            if (esta(elem)) throw EYaEnConjunto();

            insertaAux(_tabla, elem);
        }

        Conjunto<T> interseccion(const Conjunto<T> & conj) {
            Conjunto<T> ret = Conjunto<T>();

            // Los conjuntos no están ordenados, por lo que...
            ConstIterator it = cbegin();
            while (it != cend()) {
                if (conj.esta(it.elem()))
                    ret.insertaAux(ret._tabla, it.elem());

                it.next();
            }

            return ret;
        }

        Conjunto<T> either(const Conjunto<T> & conj) {
            Conjunto<T> ret = Conjunto<T>(conj);

            for (ConstIterator it = cbegin(); it != cend(); it.next()) {
                if (!ret.esta(it.elem()))
                    ret.insertaAux(ret._tabla, it.elem());
            }

            return ret;
        }

        class ConstIterator {
            public:
            void next() {
                if (_act == NULL) throw EAccesoNoValido();
                _act = _act->_sig;  // Iterador común de toda la vida

                while ((_act == NULL) && (_ind < _tabla._tam -1)) {
                    ++_ind;
                    _act = _tabla._v[_ind];
                }
            }

            const T &elem() const {
                if (_act == NULL) throw EAccesoNoValido();
                return _act->_elem;
            }

            bool operator==(const ConstIterator & other) const {
                return _act == other._act;
            }

            bool operator!=(const ConstIterator & other) const {
                return !(this->operator==(other));
            }

            protected:
            friend class Conjunto;

            ConstIterator() : _act(NULL) {}
            ConstIterator(const Tabla & tabla, Nodo * act, unsigned int ind) :
                _tabla(tabla), _act(act), _ind(ind) {}

            const Tabla & _tabla;
            Nodo * _act;    // Necesitamos tanto el nodo actual
            unsigned int _ind;  // Como el indice en la tabla
        };

        ConstIterator cbegin() const {
            unsigned int ind = 0;
            Nodo * act = _tabla._v[ind];
            while (ind < _tabla._tam-1 && act == NULL) {
                ind++;
                act = _tabla._v[ind];
            }

            return ConstIterator(_tabla, act, ind);
        }

        ConstIterator cend() const {
            return ConstIterator(_tabla, NULL, 0);
        }

        bool operator==(const Conjunto<T> & other) const {
            ConstIterator it = cbegin();

            while (it != cend()) {
                if (!other.esta(it.elem())) return false;
                it.next();
            }
            ConstIterator it2 = other.cbegin();
            while (it2 != other.cend()) {
                if (!esta(it2.elem())) return false;
                it2.next();
            }

            return true;
        }

        bool operator!=(const Conjunto<T> & other) const {
            return !(*this == other);
        }

    protected:
        static void amplia(Tabla & tabla) {
            Nodo **vAnt = tabla._v;
            unsigned int tamAnt = tabla._tam;

            tabla._tam *= 2;
            tabla._v = new Nodo*[tabla._tam];
            for (unsigned int i = 0; i < tabla._tam; ++i)
                tabla._v[i] = NULL;

            for (unsigned int i = 0; i < tamAnt; ++i) {
                Nodo * nodo = vAnt[i];
                while (nodo != NULL) {
                    Nodo * aux = nodo;
                    nodo = nodo->_sig;

                    unsigned int ind = ::h(aux->_elem) % tabla._tam;
                    aux->_sig = tabla._v[ind];
                    tabla._v[ind] = aux;
                }
            }

            delete[] vAnt;
        }

        static void insertaAux(Tabla & tabla, const T & elem) {
            // Si la ocupación es muy alta ampliamos la tabla
            float ocupacion = 100 * ((float)tabla._numElems)/tabla._tam;
            if (ocupacion > MAX_OCUPACION)
                amplia(tabla);

            unsigned int ind = ::h(elem) % tabla._tam;
            tabla._v[ind] = new Nodo(elem, tabla._v[ind]);
            tabla._numElems++;
        }

        static void buscaNodo(const T & elem, Nodo * &act, Nodo * & ant) {
            ant = NULL;
            while (act != NULL) {
                if (act->_elem == elem) {
                    return;
                } else {
                    ant = act;
                    act = act->_sig;
                }
            }
        }

        /**
         * Generalización de buscaNodo
         * Busca un nodo a partir de "prim" que contenga la clave dada.
         * A diferencia del otro método "buscaNodo", este no devuelve un puntero
         * al nodo anterior
         */
        static Nodo* buscaNodo(const T & elem, Nodo * prim) {
            Nodo * act = prim;
            Nodo * ant;
            buscaNodo(elem, act, ant);
            return act;
        }

        static void libera(Tabla & tabla) {
            for (unsigned int i = 0; i < tabla._tam; ++i)
                liberaNodos(tabla._v[i]);

            if (tabla._v != NULL) {
                delete[] tabla._v;
                tabla._v = NULL;
            }

            tabla._tam = 0;
            tabla._numElems = 0;
        }

        static void liberaNodos(Nodo * prim) {
            while (prim != NULL) {
                Nodo * aux = prim;
                prim = prim->_sig;
                delete aux;
            }
        }

        static const unsigned int MAX_OCUPACION = 80;
    };
}