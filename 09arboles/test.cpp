#include "gtest/gtest.h"
#include "01/arbin_modificado.h"
#include "02/ej02.h"

class TestArboles : public :: testing::Test {
	protected :
		Arbin<int> a0_;
		Arbin<int> hoja_;

		void SetUp() override {
			a0_ = Arbin<int>(
				Arbin<int>(
					Arbin<int> (
						Arbin<int>(),
						3,
						Arbin<int>()
					),
					2,
					Arbin<int> ()
				),
				0,
				Arbin<int>(Arbin<int>(7))
			);
			hoja_ = Arbin<int>(5);
		}
};

class TestArboles00 : public :: TestArboles {};

TEST_F(TestArboles00, raiz) {
	EXPECT_EQ(0, a0_.raiz());
	EXPECT_EQ(7, a0_.hijoDer().raiz());
}

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

class TestArboles01 : public :: TestArboles {};

/*TEST_F(TestArboles01, numNodos) {
	EXPECT_EQ(3, a0_.numNodos());
}*/

TEST_F(TestArboles01, esHoja) {
	EXPECT_TRUE(a0_.hijoDer().esHoja());
	EXPECT_FALSE(a0_.hijoIz().esHoja());
}

/** 
2. Implementa las mismas operaciones del ejercicio anterior pero como funciones externas al TAD
*/

class TestArboles02 : public :: TestArboles {};

TEST_F(TestArboles02, numNodos) {
	EXPECT_EQ(1, ej02::numNodos(hoja_));
}

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