#include "gtest/gtest.h"

#include <string>
#include "lista.h"

using namespace std;
typedef struct {
    string input;
    string output;
} tExpected;

class TestRepartir : public :: testing::TestWithParam<tExpected> {};

INSTANTIATE_TEST_SUITE_P(ITestRepartir, TestRepartir, ::testing::Values(
    tExpected {"10 5 3 10 3 20 45 3 10", "5 3 3 3 10 10 20 45 10"},
    tExpected {"10 15 20 10 25",         "10 15 20 10 25"},
    tExpected {"10 2 3 8 9",             "2 3 8 9 10"},
    tExpected {"8 5",                    "5 8"},
    tExpected {"5 8",                    "5 8"},
    tExpected {"10",                     "10"},
    tExpected {"",                       ""}
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

TEST_P(TestRepartir, Integrity) {
    Lista<int> inp = strToArr(GetParam().input);
    Lista<int> out = strToArr(GetParam().output);
    inp.repartir();
    EXPECT_EQ(inp, out);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}