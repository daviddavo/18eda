#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "pila.h"
#include "lista.h"

#include "01/ej01.h"
#include "04/ej04.h"
#include "05/ej05.h"
#include "07/ej07.h"
#include "18/ej18.h"

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

typedef struct {
    int n;
    Pila<int> in;
    Pila<int> out;
} tExpected;

class TestLineales07 : public TestLineales, public ::testing::WithParamInterface<tExpected> {};

INSTANTIATE_TEST_SUITE_P(ITestLineales, TestLineales07, ::testing::Values(
    tExpected { 0, arrtopila({6,4,3,2,3}), arrtopila({6,4,3,2,3}) },
    tExpected { 1, arrtopila({6,4,3,2,3}), arrtopila({6,4,3,2,3}) },
    tExpected { 2, arrtopila({6,4,3,2,3}), arrtopila({6,4,3,3,2}) },
    tExpected { 3, arrtopila({6,4,3,2,3}), arrtopila({6,4,3,2,3}) },
    tExpected { 4, arrtopila({6,4,3,2,3}), arrtopila({6,3,2,3,4}) },
    tExpected { 5, arrtopila({6,4,3,2,3}), arrtopila({3,2,3,4,6}) },
    tExpected { 6, arrtopila({6,4,3,2,3}), arrtopila({3,2,3,4,6}) }
));

TEST_P(TestLineales07, Invertir) {
    tExpected exp = GetParam();
    ej07::invertir(exp.in, exp.n);
    EXPECT_EQ(exp.in, exp.out);
}

class TestListas : public ::testing::Test {
    protected:
    Lista<int> _l0;
    Lista<int> _l1;
    
    void SetUp() override {
        for (int i = 0; i < 10; i++)
            _l1.pon_final(i);      
    }
};

class TestLineales18 : public TestListas {};

TEST_F(TestLineales18, InsertarPosicion) {
    ej18::ListaMejorada<int> l1sin3;

    EXPECT_THROW(l1sin3.insertarPorPosicion(0, -3), EAccesoInvalido);
    EXPECT_THROW(l1sin3.insertarPorPosicion(0, 57), EAccesoInvalido);

    for (int i = 0; i < 3; i++)
        l1sin3.insertarPorPosicion(i, i);
    for (int i = 4; i < 10; i++)
        l1sin3.insertarPorPosicion(i, i-1); // Poner al final (falta el 3)

    // Testeamos la insercción en la primera mitad
    l1sin3.insertarPorPosicion(3,3);
    EXPECT_EQ(l1sin3, _l1);

    // Ahora con la segunda mitad
    ej18::ListaMejorada<int> l1sin7;
    for (int i = 0; i < 7; i++)
        l1sin7.insertarPorPosicion(i, i);
    for (int i = 8; i < 10; i++)
        l1sin7.insertarPorPosicion(i, i-1);

    l1sin7.insertarPorPosicion(7,7);
    EXPECT_EQ(l1sin7, _l1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}