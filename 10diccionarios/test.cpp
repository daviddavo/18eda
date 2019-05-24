#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "c08/c08.h"

class TestDiccionarios : public :: testing::Test {
	protected :
		vector <string> input;
		vector <string> output;

		void SetUp() override {
			input.push_back("# jose + jose - jose - lucas + pedro - lucas - #");
			input.push_back("# jose + jose - jose - jose + #");
			input.push_back("# #");
			input.push_back("# jose - juan + juan + #");

			output.push_back("[jose:-1][pedro:-1]");
			output.push_back("[jose:-1][juan:2]");
			output.push_back("");
			output.push_back("");
		}
};

class TestDiccionariosC08 : public :: TestDiccionarios {};

TEST_F(TestDiccionariosC08, integrity) {
	for (int i = 0; i < input.size(); ++i) {
		Lista <string> bien = Lista<string>(), mal = Lista<string>();
		Lista <Puntuacion> listado = Lista<Puntuacion>();
		stringstream ssinput, ssoutput;
		ssinput.str(input[i]);
		leeResultados(ssinput, bien, mal);
		califica(bien, mal, listado);
		imprimePuntuaciones(ssoutput, listado);
		EXPECT_EQ(ssoutput.str(), output[i]);
	}
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}