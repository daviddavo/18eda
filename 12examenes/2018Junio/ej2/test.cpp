#include "gtest/gtest.h"
#include <sstream>


#include "Arbin.h"
#include "main.h"

using namespace std;

typedef struct {
    string input;
    int output;
} tExpected;

/*
class TestCaballeros : public :: testing:TestWithParam<tExpected> {}

INSTANTIATE_TEST_SUITE_P(ITestCaballeros, TestCaballeros, ::testing.Values(
    {"((([C]D#)M([C]D[C]))M((#D([C]C[C]))M[D]))", 2}
));

TEST_P(TestCaballeros, Integrity) {
    tExpected exp = GetParam();
    stringstream ss = stringstream(exp.input);
    Arbin<char> arbol = lee_arbol(ss);
    EXPECT_EQ(num_a_salvo(arbol), exp.output);
}*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}