#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include <iostream>

// #include "01/ej01.h"
#include "03/ej03.h"
#include "05/conjunto.h"
#include "06/ej06.h"
#include "c08/c08.h"
using namespace std;

class TestDiccionarios : public :: testing::Test {
	protected:
	Diccionario<int, int> d0_;	
	Diccionario<int, int> d1_;
	Diccionario<int, int> d2_;

	void SetUp() override {
		/**   30:0
		 *    /
		 *  20:0
		 *  /
		 * 10:0
		 */
		d0_.inserta(30, 0);
		d0_.inserta(20, 0);
		d0_.inserta(10, 0);

		d1_.inserta(4, 0);
		d1_.inserta(3, 0);
		d1_.inserta(2, 0);
		d1_.inserta(1, 0);

		/**
		 * 		 4
		 *      / \
		 *     3   5
		 *    /     \
		 *   2       6
		 *  /         \
		 * 1           7
		 */
		d2_.inserta(4, 0);
		d2_.inserta(3, 0);
		d2_.inserta(2, 0);
		d2_.inserta(1, 0);
		d2_.inserta(5, 0);
		d2_.inserta(6, 0);
		d2_.inserta(7, 0);
	}
};

// TestDiccionarios01 on 01/ej01.h

class TestDiccionarios03 : public :: TestDiccionarios {};

TEST_F(TestDiccionarios03, consultaK) {
	ej03::DiccionarioMejorado<int,int> d0mejorado = ej03::DiccionarioMejorado<int,int>(d0_);

	EXPECT_THROW(d0mejorado.consultaK(-5), EAccesoNoValido);
	EXPECT_THROW(d0mejorado.consultaK(3), EAccesoNoValido);
	EXPECT_EQ(d0mejorado.consultaK(0), 10);
	EXPECT_EQ(d0mejorado.consultaK(1), 20);
	EXPECT_EQ(d0mejorado.consultaK(2), 30);

	ej03::DiccionarioMejorado<int,int> d2mejorado = ej03::DiccionarioMejorado<int,int>(d2_);

	EXPECT_THROW(d2mejorado.consultaK(7), EAccesoNoValido);
	for (int i = 0; i < 6; i++) EXPECT_EQ(d2mejorado.consultaK(i), i+1);
}

TEST_F(TestDiccionarios03, recorreRango) {
	auto d0mejorado = ej03::DiccionarioMejorado<int, int>(d0_);

	EXPECT_THROW(d0mejorado.recorreRango(0, 2), EClaveErronea);
	EXPECT_THROW(d0mejorado.recorreRango(10, 2), EClaveErronea);
	EXPECT_THROW(d0mejorado.recorreRango(10, 50), EClaveErronea);

	auto d0lista = Lista<int>();

	d0lista.pon_final(10);
	EXPECT_EQ(d0mejorado.recorreRango(10, 10), d0lista);

	d0lista.pon_final(20);
	EXPECT_EQ(d0mejorado.recorreRango(10, 20), d0lista);

	auto d2mejorado = ej03::DiccionarioMejorado<int, int>(d2_);
	auto d2lista = Lista<int>();
	for (int i = 2; i <= 4; i++)
		d2lista.pon_final(i);

	EXPECT_EQ(d2mejorado.recorreRango(2, 4), d2lista);
}

TEST_F(TestDiccionarios03, erase) {
	auto d0mejorado = ej03::DiccionarioMejorado<int, int>(d0_);
	auto d0mejoradoBorrado = ej03::DiccionarioMejorado<int, int>(Diccionario<int,int>(d0_));
	d0mejoradoBorrado.borra(10);

	EXPECT_THROW(d0mejorado.erase(d0mejorado.end()), EAccesoInvalido);
	auto it = d0mejorado.erase(d0mejorado.begin());

	// FIXME: Throws EAccesoNoValido
	EXPECT_EQ(d0mejorado, d0mejoradoBorrado);
	EXPECT_TRUE(false);	// Ejercicio por terminar
}

class TestDiccionarios05 : public :: testing::Test {
	protected:
	ej05::Conjunto<int> c0_;
	ej05::Conjunto<int> c1_;
	ej05::Conjunto<int> c2_;
	ej05::Conjunto<int> c1interc2_;
	ej05::Conjunto<int> c1unionc2_;
	ej05::Conjunto<int> c1difc2_;
	ej05::Conjunto<int> c2difc1_;

	void SetUp() override {
		// c0_ = "Conjunto Vacío"
		for (int i = 0; i < 20; ++i)
			c1_.inserta(i);

		for (int i = 10; i < 30; ++i)
			c2_.inserta(i);

		for (int i = 10; i < 20; ++i)
			c1interc2_.inserta(i);

		for (int i = 0; i < 30; ++i)
			c1unionc2_.inserta(i);

		for (int i = 0; i < 10; ++i)
			c1difc2_.inserta(i);

		for (int i = 20; i < 30; ++i)
			c2difc1_.inserta(i);
	}
};

TEST_F(TestDiccionarios05, ConjuntoVacio) {
	EXPECT_NO_THROW(ej05::Conjunto<int>());
	EXPECT_NO_THROW(ej05::Conjunto<int>(10));
}

TEST_F(TestDiccionarios05, Contiene) {
	EXPECT_FALSE(c0_.esta(10));
	c0_.inserta(10);
	EXPECT_TRUE(c0_.esta(10));
}

TEST_F(TestDiccionarios05, Inserta) {
	EXPECT_NO_THROW(c0_.inserta(10));
	EXPECT_THROW(c0_.inserta(10), EYaEnConjunto);
}

TEST_F(TestDiccionarios05, InsertaCollisions) {
	for (int i = 0; i < 1000000; ++i) {
		EXPECT_FALSE(c0_.esta(i));
		EXPECT_NO_THROW(c0_.inserta(i));
		EXPECT_TRUE(c0_.esta(i));
	}
}

TEST_F(TestDiccionarios05, Equals) {
	EXPECT_EQ(c0_, ej05::Conjunto<int>());
	EXPECT_EQ(c1_, c1_);
	ej05::Conjunto<int> c1copia = ej05::Conjunto<int>();
	for (int i = 0; i < 20; ++i)
		c1copia.inserta(i);
	EXPECT_EQ(c1_, c1copia);

	EXPECT_NE(c1_, c2_);
}

TEST_F(TestDiccionarios05, Interseccion) {
	EXPECT_EQ(c0_.interseccion(c1_), ej05::Conjunto<int>());
	EXPECT_EQ(c1_.interseccion(c0_), ej05::Conjunto<int>());

	EXPECT_EQ(c1_.interseccion(c2_), c1interc2_);
	EXPECT_EQ(c2_.interseccion(c1_), c1interc2_);
}

TEST_F(TestDiccionarios05, Union) {
	EXPECT_EQ(c0_.either(c1_), c1_);
	EXPECT_EQ(c1_.either(c0_), c1_);

	EXPECT_EQ(c1_.either(c2_), c1unionc2_);
	EXPECT_EQ(c2_.either(c1_), c1unionc2_);
}

TEST_F(TestDiccionarios05, Diferencia) {
	EXPECT_EQ(c1_.diferencia(c0_), c1_);
	EXPECT_EQ(c0_.diferencia(c1_), c0_);

	EXPECT_EQ(c1_.diferencia(c2_), c1difc2_);
	EXPECT_EQ(c2_.diferencia(c1_), c2difc1_);
}

class TestDiccionarios06 : public :: testing::Test {
	protected:
	DiccionarioHash<int, int> d0_;

	void SetUp() override {
		// d0_ is empty
	}
};

// Siendo la funcion hash(int) return int;
TEST_F(TestDiccionarios06, IndiceRadial) {
	int i;
	for (i = 0; i < 8; ++i) {
		EXPECT_EQ((DiccionarioRadial<int, int>(d0_)).indRadial(), (unsigned)(DiccionarioHash<int,int>::TAM_INICIAL)*i);
		d0_.inserta(i*8, 0);
	}

	for (; i < 15; ++i) {
		EXPECT_EQ((DiccionarioRadial<int, int>(d0_)).indRadial(), 16*i-8*8);
		d0_.inserta(i*16, 0);
	}
}

class TestDiccionariosC08 : public :: TestDiccionarios {
	protected :
		vector <string> input;
		vector <string> output;

		void SetUp() override {
			input.push_back("jose + jose - jose - lucas + pedro - lucas - #");
			input.push_back("jose + jose - jose - jose + #");
			input.push_back("#");
			input.push_back("jose - juan + juan + #");

			output.push_back("[jose:-1][pedro:-1]");
			output.push_back("");
			output.push_back("");
			output.push_back("[jose:-1][juan:2]");
		}
};

TEST_F(TestDiccionariosC08, integrity) {
	for (int i = 0; i < input.size(); ++i) {
		Lista <string> bien = Lista<string>(), mal = Lista<string>();
		Lista <Puntuacion> listado = Lista<Puntuacion>();
		stringstream ssinput, ssoutput;
		ssinput << input[i] << endl;

		leeResultados(ssinput, bien, mal);
		califica(bien, mal, listado);
		imprimePuntuaciones(ssoutput, listado);
		EXPECT_EQ(output[i], ssoutput.str());
	}
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}