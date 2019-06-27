#include "ParqueNatural.h"

/* 
    Complejidad O(1)
*/
ParqueNatural::ParqueNatural() {

}

/* 
    La complejidad de añadir un elemento en un BST + comprobar que no está
    Ambos son de complejidad O(n) en el peor de los casos y O(log n) si el arbol
    está balanceado
*/
void ParqueNatural::an_ecosistema(const string& ecosistema) {
    if (_ecosistemasParque.contiene(ecosistema)) throw EEcosistemaDuplicado();

    _ecosistemasParque.inserta(ecosistema, InfoEcosistema());
}

void ParqueNatural::InfoEcosistema::an_ejemplares(const tEspecie & especie, int n) {
    if (_nEspecies.contiene(especie))
        n += _nEspecies.valorPara(especie);
    else 
        _recientes.pon_ppio(especie);
    
    _nEspecies.inserta(especie, n);
}

/* 
    Tanto contiene, valorPara como inserta tienen la misma complejidad que buscar un 
    elemento en un BST, O(n) en el peor de los casos, O(log n) si está balanceado
*/
void ParqueNatural::an_ejemplares(const string& ecosistema, const string& especie, int n) {
    if (!_ecosistemasParque.contiene(ecosistema)) throw EEcosistemaNoExiste();
    ParqueNatural::InfoEcosistema tmp = _ecosistemasParque.valorPara(ecosistema);
    tmp.an_ejemplares(especie, n);
    _ecosistemasParque.inserta(ecosistema, tmp);
    
    /** Actualizamos el número de ejemplares de esa especie */
    if (_especiesParque.contiene(especie)) n += _especiesParque.valorPara(especie);
    
    _especiesParque.inserta(especie, n);
}

Lista<tEspecie> ParqueNatural::InfoEcosistema::lista_especies(int n) const {
    Lista<tEspecie> ret;

    int i = 0;
    auto it = _recientes.cbegin();
    while (i < n && it != _recientes.cend()) {
        ret.pon_final(it.elem());
        
        it.next();
        ++i;
    }

    return ret;
}

/* 
    En el peor de los casos tendrá complejidad n, pues tendremos que hacer una
    copia completa de toda la lista pasando por todos los nodos.
    Como hay que hacer una copia del array, no hubiese mejorado la complejidad
    usando otra implementacion sin nodos enlazados
*/
Lista<tEspecie> ParqueNatural::lista_especies_ecosistema(const string& ecosistema, int n) const {
    if (!_ecosistemasParque.contiene(ecosistema)) throw EEcosistemaNoExiste();

    return _ecosistemasParque.valorPara(ecosistema).lista_especies(n);
}

int ParqueNatural::InfoEcosistema::numero_ejemplares(const tEspecie & especie) const {
    if (!_nEspecies.contiene(especie)) return 0;

    return _nEspecies.valorPara(especie);
}

/* 
    La complejidad de buscar un elemento en un BST
    Ambos son de complejidad O(n) en el peor de los casos y O(log n) si el arbol
    está balanceado
*/
int ParqueNatural::numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const {
/* A IMPLEMENTAR */
    if (!_ecosistemasParque.contiene(ecosistema)) throw EEcosistemaNoExiste();
    return _ecosistemasParque.valorPara(ecosistema).numero_ejemplares(especie);
}

/* 
    Tiene tanta complejidad como recorrer en preorden un BST, O(n)
    Pues poner al final de una lista de nodos enlazados un elemento tiene
    coste constante
*/
Lista<tEspecie> ParqueNatural::lista_especies_parque() const {
    Lista<tEspecie> ret;
    for (auto it = _especiesParque.cbegin(); it != _especiesParque.cend(); it.next())
        ret.pon_final(it.clave());

    return ret;
}

/* 
    Tanta complejidad como buscar en un BST, balanceado O(log n), no balanceado O(n)
*/
int ParqueNatural::numero_ejemplares_en_parque(const string& especie) const {
    if(!_especiesParque.contiene(especie)) return 0;

    return _especiesParque.valorPara(especie);
}
 