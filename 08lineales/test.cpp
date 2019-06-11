#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "pila.h"

#include "01/ej01.h"

using namespace std;

template <class T, size_t N>
Pila<T> arrtopila(T (&arr) [N]) {
    Pila<T> ret = Pila<T>();

    for (int i = 0; i < N; ++i)
        ret.apila(arr[i]);

    return ret;
}

class TestLineales : public :: testing::Test {
protected:
    Pila<int> p1;

    void SetUp() override {
        int p1arr[] {6,4,3,2,3};
        p1 = arrtopila(p1arr);
    }
};

class TestLineales01 : public :: TestLineales {};

TEST_F(TestLineales01, suma) {
    stringstream ss;
    ej01(ss, 64323);
    EXPECT_EQ(ss.str(), "6 + 4 + 3 + 2 + 3 = 18");
    ss.str("");
    ej01(ss, 12345);
    EXPECT_EQ(ss.str(), "1 + 2 + 3 + 4 + 5 = 15");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}