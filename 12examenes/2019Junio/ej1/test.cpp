#include "gtest/gtest.h"

#include <string>
#include "lista.h"

using namespace std;

typedef struct {
    string input;
    string output;
} tExpected;

class TestEstremecer : public :: testing::TestWithParam<tExpected> {};

INSTANTIATE_TEST_SUITE_P(ITestEstremecer, TestEstremecer, ::testing::Values(
    tExpected {"0 1 2 3 4 5 6 7",   "0 2 4 6 7 5 3 1"},
    tExpected {"5 7 9 10 20 25",  "5 9 20 25 10 7"},
    tExpected {"6 8 2 1",         "6 2 1 8"},
    tExpected {"0 1 2",             "0 2 1"},
    tExpected {"0 1",               "0 1"},
    tExpected {"0",                 "0"},
    tExpected {"",                 ""}
));

Lista<int> strToArr(const string & str) {
    Lista<int> ret;
    int valor;
    stringstream ss;

    ss.str(str);
    while (ss >> valor)
        ret.pon_final(valor);

    return ret;
}

TEST_P(TestEstremecer, Integrity) {
    Lista<int> input = strToArr(GetParam().input);
    Lista<int> output = strToArr(GetParam().output);
    input.estremece();
    EXPECT_EQ(input, output);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}