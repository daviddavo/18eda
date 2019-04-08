/**
Este programa lee árboles de la entrada estándar, 
codificados de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada árbol leído, escribe en la salida estándar
el número de nodos singulares de dicho árbol.
	
Algunos casos representativos:

#
[0]
[5]
(([4]3[-3])1[-4])

-El primero representa el árbol vacío. Al no tener nodos,
un árbol vacío tiene 0 nodos sigulares.
-El segundo representa un árbol con un único nodo, cuyo valor
es 0. Dicho nodo es singular, ya que: (i) como no tiene 
ascestros, la suma de los ancestros es 0, (ii) como no
tiene descendientes, la suma de los descendientes es 0. 
-El tercero representa otro árbol con un único nodo, cuyo
valor es 5. Por la misma razón que en el segundo ejemplo,
este nodo es singular.
-El cuarto representa el siguiente árbol:
     
	       1
		  /  \
		  3  -4
         / \  
        4  -3 

Este árbol tiene 2 nodos sigulares: la raíz, y la raíz del hijo 
izquierdo. 

Por tanto, la salida del programa para estos casos será:

0
1
1
2

*/
#include "c07.h"
#include <iostream>
#include <string>

using namespace std;


/**
  COMPLEJIDAD: Es de n^2 pues se recorre, para cada uno de los nodos, todos los nodos subyacentes.
*/
/*
unsigned int numero_singulares(const Arbin<int>& a, int sumaAntes, int & sumaDespues) {
	if (a.esVacio()) {
		sumaDespues = 0;
		return 0;
	}
	if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {
		sumaDespues = a.raiz();
		return (sumaAntes == sumaDespues)?1:0;
	}

	int sumaDespuesIzda;
	int sumaDespuesDcha;
	int singIzda = 0, singDcha = 0;
	singIzda = numero_singulares(a.hijoIz(), sumaAntes + a.raiz(), sumaDespuesIzda);
	singDcha = numero_singulares(a.hijoDer(), sumaAntes + a.raiz(), sumaDespuesDcha);

	sumaDespues = sumaDespuesIzda + sumaDespuesDcha;
	return singIzda + singDcha + (sumaAntes == sumaDespues)?1:0;
}*/

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		cout << numero_singulares(lee_arbol(cin));
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
