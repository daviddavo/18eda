#include "sol.h"

/**
 * EN el desarrollo de un juego de aventuras conversacionales se está
 * representando el mapa del juego mediante un árbol binario de personajes.
 * En cada nodo del árbol hay un personaje (mostruo, caballero o dama) representado
 * a través de un carácter ('M', 'C' y 'D').
 * 
 * Se dice que un nodo está a salvo cuando:
 * i) En él hay una dama
 * ii) El número de monstruos que hay en el camino que va desde la raiz a dicho
 * 	   nodo es menor o igual que hay en los nodos descendientes de dicho nodo
 */

/**
 * La complejidad de esto es lineal, donde n es el numero de nodos del arbol binario
 * Se recorre una vez cada nodo, ni una más, ni una menos.
 * O(n)
 * 
 * (Con la implementación de arbol binario por referencias, en el que la copia
 * tiene coste constante)
*/
int num_a_salvo(const Arbin<char>& a, int monstruos, int & caballeros) {
	if (a.esVacio()) return 0;

	int ret = 0;

	if (a.raiz() == 'M') monstruos += 1;
	int caballerosIzda = 0;
	int caballerosDcha = 0;
	ret += num_a_salvo(a.hijoIz(), monstruos, caballerosIzda);
	ret += num_a_salvo(a.hijoDer(), monstruos, caballerosDcha);

	caballeros = caballerosIzda + caballerosDcha;
	if (a.raiz() == 'C') caballeros += 1;
	else if (a.raiz() == 'D' && caballeros >= monstruos) ret += 1;

	return ret;  
}

int num_a_salvo(const Arbin<char>& a) {
	int basura;
	return num_a_salvo(a, 0, basura);
}



Arbin<char> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
  		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = lee_arbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = lee_arbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}