#include "gtest/gtest.h"

/**
1. Extiende la implementación de los arboles binarios con las siguientes operaciones
	- numNodos: devuelve el numero de nodos del arbol
	- esHoja: devuelve cierto si el arbol es una hoja (los hijos izquierdo y derecho son vacios)
	- numHojas: devuelve el numero de hojas del arbol
	- talla: devuelve la talla del arbol
	- frontera: devuelve una lista con todas las hojas del arbol de izquierda a derecha
	- espejo: devuelve un arbol nuevo que es la imagen especular del original
	- minElem: devuelve el elemento mas pequeño de todos los almacenados en el arbol. 
		Es un error ejecutar esta operacion sobre una arbol vacio
*/

TEST(TestArboles01, numNodos) {
	ASSERT_EQ(4, 2+2);
}

/** 
2. Implementa las mismas operaciones del ejercicio anterior pero como funciones externas al TAD
*/

/**
3.	Implementa una función recursiva template <class T> void printArbol(const Arbin<T> &arbol);
	que escriba por pantalla el arbol que recibe por parametro, segun las siguientes reglas:
	-	Si el arbol es vacio, escribira <vacio> y despues retorno de carro
	-	Si el arbol es un arbol hoja, escribira el contenido de la raiz y un retorno de carro
	-	Si el arbol tiene algun hijo, escribira el contenido del nodo raiz, y recursivamente en 
		las siguientes lineas el hijo izquierdo y despues el hijo derecho. Los hijos izquierdo y derecho están
		tabulados, dejando tres espacios
*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}