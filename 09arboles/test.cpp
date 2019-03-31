#include <sstream>
#include <string>
#include "gtest/gtest.h"
// #include "01/arbin_modificado.h"
#include "02/ej02.h"
#include "03/ej03.h"
#include "c06/c06.h"

class TestArboles : public :: testing::Test {
	protected :
		Arbin<int> a0_;
        Arbin<int> a1_; // From c06
        Arbin<int> a0Espejo_;
		Arbin<int> hoja_;
        Arbin<int> vacio_;

		void SetUp() override {
			a0_ = Arbin<int>(
				Arbin<int>(
					Arbin<int> (
						Arbin<int>(6),
						3,
						Arbin<int>(8)
					),
					2,
					Arbin<int> (4)
				),
				0,
				Arbin<int>(Arbin<int>(7))
			);

            a0Espejo_ = Arbin<int>(
                Arbin<int>(Arbin<int>(7)),
                0,
                Arbin<int>(
                    Arbin<int>(4),
                    2,
                    Arbin<int>(
                        Arbin<int>(8),
                        3,
                        Arbin<int>(6)
                    )
                )
            );

            a1_ = Arbin<int>(
                Arbin<int>(2),
                1,
                Arbin<int>(
                    Arbin<int>(4),
                    3,
                    Arbin<int>(5)
                )
            );

			hoja_ = Arbin<int>(5);

            vacio_ = Arbin<int>();
		}
};

class TestArboles00 : public :: TestArboles {};

TEST_F(TestArboles00, raiz) {
	EXPECT_EQ(0, a0_.raiz());
	EXPECT_EQ(7, a0_.hijoDer().raiz());
    EXPECT_EQ(5, hoja_.raiz());
    ASSERT_THROW(vacio_.raiz(), EArbolVacio);
}

TEST_F(TestArboles00, vacio) {
    EXPECT_FALSE(a0_.esVacio());
    EXPECT_FALSE(hoja_.esVacio());
    EXPECT_TRUE(vacio_.esVacio());
}

TEST_F(TestArboles00, equ) {
    EXPECT_EQ(a0_, a0_);
    EXPECT_NE(a0_, a0Espejo_);
    EXPECT_EQ(a0_, Arbin<int>(a0_));
    EXPECT_EQ(vacio_, Arbin<int>());
    EXPECT_NE(vacio_, hoja_);
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

/** 
2. Implementa las mismas operaciones del ejercicio anterior pero como funciones externas al TAD
*/

class TestArboles02 : public :: TestArboles {};

TEST_F(TestArboles02, numNodos) {
	EXPECT_EQ(1, ej02::numNodos(hoja_));
    EXPECT_EQ(7, ej02::numNodos(a0_));
    EXPECT_EQ(0, ej02::numNodos(vacio_));
}

TEST_F(TestArboles02, esHoja) {
    EXPECT_TRUE(ej02::esHoja(hoja_));
    EXPECT_FALSE(ej02::esHoja(a0_));
    EXPECT_THROW(ej02::esHoja(vacio_), EArbolVacio);
}

TEST_F(TestArboles02, numHojas) {
    EXPECT_EQ(1, ej02::numHojas(hoja_));
    EXPECT_EQ(4, ej02::numHojas(a0_));
}

TEST_F(TestArboles02, talla) {
    EXPECT_EQ(1, ej02::talla(hoja_));
    EXPECT_EQ(4, ej02::talla(a0_));
}

TEST_F(TestArboles02, espejo) {
    EXPECT_EQ(ej02::espejo(a0_), a0Espejo_);
    EXPECT_EQ(a0_, ej02::espejo(a0Espejo_));
    EXPECT_EQ(a0_, ej02::espejo(ej02::espejo(a0_)));
}

TEST_F(TestArboles02, minElem) {
    EXPECT_THROW(ej02::minElem(vacio_), EArbolVacio);
    EXPECT_EQ(0, ej02::minElem(a0_));
    EXPECT_EQ(1, ej02::minElem(a1_));
    EXPECT_EQ(5, ej02::minElem(hoja_));
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

// TODO: Parametrizar este test
class TestArboles03 : public :: TestArboles {
protected:

};

TEST_F(TestArboles03, print) {
    stringstream ss;
    ej03::printArbol(vacio_, ss);
    EXPECT_EQ("<vacio>\n", ss.str());
    
    ss.str("");
    ej03::printArbol(hoja_, ss);
    EXPECT_EQ("5\n", ss.str());
}

class TestArbolesC06 : public :: TestArboles {};

TEST_F(TestArbolesC06, numeroHojasMasProfundasQue) {
    EXPECT_EQ(0, numero_hojas_mas_profundas_que(vacio_, 0));
    EXPECT_EQ(0, numero_hojas_mas_profundas_que(vacio_, 1));
    EXPECT_EQ(0, numero_hojas_mas_profundas_que(vacio_, 2));

    EXPECT_EQ(1, numero_hojas_mas_profundas_que(hoja_, 0));
    EXPECT_EQ(0, numero_hojas_mas_profundas_que(hoja_, 1));

    EXPECT_EQ(0 , numero_hojas_mas_profundas_que(a0_, 4));
    EXPECT_EQ(2 , numero_hojas_mas_profundas_que(a0_, 3));
    EXPECT_EQ(3 , numero_hojas_mas_profundas_que(a0_, 2));
    EXPECT_EQ(4 , numero_hojas_mas_profundas_que(a0_, 1));

    // Enunciado de C06
    EXPECT_EQ(3, numero_hojas_mas_profundas_que(a1_, 0));
    EXPECT_EQ(3, numero_hojas_mas_profundas_que(a1_, 1));
    EXPECT_EQ(2, numero_hojas_mas_profundas_que(a1_, 2));
    EXPECT_EQ(0, numero_hojas_mas_profundas_que(a1_, 3));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}