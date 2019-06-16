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
	}
};

// TestDiccionarios01 on 01/ej01.h

class TestDiccionarios03 : public :: TestDiccionarios {};

TEST_F(TestDiccionarios03, consultaK) {
	ej03::DiccionarioMejorado<int,int> d0mejorado_ = ej03::DiccionarioMejorado<int,int>(d0_);

	EXPECT_THROW(d0mejorado_.consultaK(-5), EAccesoNoValido);
	EXPECT_THROW(d0mejorado_.consultaK(5), EAccesoNoValido);
	EXPECT_EQ(d0mejorado_.consultaK(0), 10);
	EXPECT_EQ(d0mejorado_.consultaK(1), 20);
	EXPECT_EQ(d0mejorado_.consultaK(2), 30);
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