#include "c06.h"
#include <iostream>
#include <string>

using namespace std;

/**
  COMPLEJIDAD:
  Depende de la complejidad de las funciones implementadas en el arbol.
  Por lo tanto:
    ----------------
    -- ARBOL BINARIO EFICIENTE
    ----------------
    Todas las operaciones son de complejidad (temporal y de memoria) O(1),
    por lo que nuestra función, en el peor de los casos, tendrá una complejidad
    O(n) pues tendrá que acceder a todos y cada uno de los nodos del arbol
    para comprobar su profundidad. Este caso ocurre cuando ponemos una k mayor
    o igual que la talla del arbol.

    ----------------
    -- ARBOL BINARIO INEFICIENTE
    ----------------
    Las operaciones de acceso a los hijos necesitan hacer una copia y, por lo
    tanto serán de complejidad O(n'), donde n' es el numero de nodos del hijo.
    El peor de los casos se da con un arbol binario en el que todos los nodos
    tienen dos hijos, por lo que n' (cantidad de nodos en el hijo) será n/2-1
    y las operaciones hijoIz o hijoDer pertenecen a O(n)

    Si ponemos una k mayor o igual que la talla del arbol, tendremos que acceder
    a todos los nodos, y, para cada uno de los accesos, acceder a todos los
    nodos siguientes, por lo que tendremos O(n^2)

*/
// La función está definida en c06.h, de esa manera se puede importar en otros
// archivos o testearse con xUnit

Arbin<int> lee_arbol(istream& in) {
    char c;
    in >> c;
    switch (c) {
    case '#': return Arbin<int>();
    case '[': {
        int raiz;
        in >> raiz;
        in >> c;
        return Arbin<int>(raiz);
    }
    case '(': {
        Arbin<int> iz = lee_arbol(in);
        int raiz;
        in >> raiz;
        Arbin<int> dr = lee_arbol(in);
        in >> c;
        return Arbin<int>(iz, raiz, dr);
    }
    default: return Arbin<int>();
    }
}

/**
La entrada al programa consiste de líneas formadas por:
(1) Un árbol de enteros
(2) El valor de k
Los árboles se codifican de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
    v el valor de la raíz, y D la codificación
    del hijo derecho.
Para cada línea leida, escribe en la salida estádar
el número de hojas que están a profundidad mayor que k

    
Ejemplo de entrada:

([2]1([4]3[5])) 0
([2]1([4]3[5])) 1
([2]1([4]3[5])) 2
([2]1([4]3[5])) 3
([2]1([4]3[5])) 4
([2]1([4]3[5])) 100

Salida asociada:

3
3
2
0
0
0

*/


int main() {
    Arbin<int> arbol;
    while (cin.peek() != EOF)  {
        Arbin<int> a = lee_arbol(cin);
        int k;
        cin >> k;
        cout << numero_hojas_mas_profundas_que(a,k) << endl;
        string resto_linea;
        getline(cin, resto_linea);
    }
    return 0;
}
