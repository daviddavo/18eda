#include <sstream>
#include "gtest/gtest.h"

#include "c08/c08.h"

class TestDiccionarios : public :: testing::Test {
	protected :
		string input[];
		string output[];
		int N;

		void setUp() override {
			N = 4;

			input = [
				"# jose + jose - jose - lucas + pedro - lucas - #",
				"# jose + jose - jose - jose + #",
				"# #",
				"# jose - juan + juan + #"
			];

			output = [
				"[jose:-1][pedro:-1]",
				"[jose:-1][juan:2]",
				"",
				""
			];
		}
}

class TestDiccionariosC08 : public :: TestDiccionarios {};

TEST_F(TestDiccionariosC08, integrity) {
	for (int i = 0; i < N; ++i) {
		stringstream ssinput, ssoutput;
		ssinput.str(input);
		lee
	}
}