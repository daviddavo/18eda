#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include <iostream>

// #include "01/ej01.h"
#include "03/ej03.h"
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
	d0mejorado.erase(d0mejorado.begin());

	// FIXME: Throws EAccesoNoValido
	EXPECT_EQ(d0mejorado, d0mejoradoBorrado);
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