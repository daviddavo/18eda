#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "pila.h"

#include "01/ej01.h"
#include "04/ej04.h"
#include "05/ej05.h"

using namespace std;

template <class T, size_t N>
Pila<T> arrtopila(const T (&arr) [N]) {
    Pila<T> ret = Pila<T>();

    for (int i = 0; i < N; ++i)
        ret.apila(arr[i]);

    return ret;
}

template <class T, size_t N>
string arrtostr(const T (&arr) [N]);

template <size_t N>
string arrtostr(const int (&arr) [N]) {
    string ret;

    for (int i = 0; i < N; ++i)
        ret += to_string(arr[i]) + "\n";

    return ret;
}

class TestLineales : public :: testing::Test {
protected:
    Pila<int> p1;
    string p1str;

    void SetUp() override {
        p1 = arrtopila({6,4,3,2,3});
        p1str = arrtostr({6,4,3,2,3});
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

class TestLineales04 : public :: TestLineales {};

TEST_F(TestLineales04, Posfija) {
    EXPECT_EQ(ej04::posFija("821-/82+*"), 80);
}

class TestLineales05 : public :: TestLineales {};

TEST_F(TestLineales05, Recursivo) {
    stringstream ss;
    ej05::imprimeRecursivo(ss, p1);
    EXPECT_EQ(ss.str(), p1str);
}

TEST_F(TestLineales05, Iterativo) {
    stringstream ss;
    ej05::imprimeIterativo(ss, p1);
    EXPECT_EQ(ss.str(), p1str);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}