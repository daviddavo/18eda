#include "gtest/gtest.h"
#include <sstream>
#include <string>

#include "Arbin.h"
#include "sol.h"

using namespace std;

typedef struct {
    string input;
    int output;
} tExpected;

class TestCaballeros : public :: testing::TestWithParam<tExpected> {};

INSTANTIATE_TEST_SUITE_P(ITestCaballeros, TestCaballeros, ::testing::Values(
    tExpected {"((([C]D#)M([C]D[C]))M((#D([C]C[C]))M[D]))", 2},
    tExpected {"[M]", 0},
    tExpected {"[D]", 1}
));

TEST_P(TestCaballeros, Integrity) {
    tExpected exp = GetParam();
    printf("Param: {%s, %d\n}", GetParam().input.c_str(), GetParam().output);
    stringstream ss;
    ss.str(GetParam().input);
    Arbin<char> arbol = lee_arbol(ss);
    EXPECT_EQ(num_a_salvo(arbol), exp.output);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}