#include <sstream>
#include "gtest/gtest.h"

#include "01/01.h"

class TestAplicaciones : public :: testing::Test {};

class TestAplicaciones01 : public :: TestAplicaciones {
    protected:
    BigVector _bv0;
    BigVector _bv1;
    BigVector _bv2;
    BigVector _bv3;
    BigVector _bv2pbv3;
    BigVector _bv2squared;
    BigVector _bv2twice;

    void SetUp() override {
        // _bv1 es el "vector unitario"
        for (int i = 0; i < 1024; ++i)
            _bv1.ponValor(i, 1);

        // _bv0 always 0
        for (int i = 0; i < 256; i++)
            _bv2.ponValor(i, i);
        
        for (int i = 256; i < 512; i++)
            _bv3.ponValor(i, i);

        // bv2 y bv3 son ortogonales
        for (int i = 0; i < 512; i++)
            _bv2pbv3.ponValor(i, i);

        for (int i = 0; i < 256; i++)
            _bv2squared.ponValor(i, i*i);

        for (int i = 0; i < 256; i++)
            _bv2twice.ponValor(i, 2*i);
    }
};

TEST_F(TestAplicaciones01, BigVector_create) {
    ASSERT_NO_THROW(BigVector());
    for (int i = 0; i < 265; ++i)
        ASSERT_EQ(_bv0.valorDe(i), 0);
}

TEST_F(TestAplicaciones01, BigVector_ponValorValorDe) {
    for (int i = 0; i < 256; ++i)
        ASSERT_EQ(_bv2.valorDe(i), i);

    for (int i = 0; i < 5; i++)
        _bv2.ponValor(i, 0);

    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(_bv2.valorDe(i), 0);
}

TEST_F(TestAplicaciones01, BigVector_productoEscalar) {
    EXPECT_EQ(_bv0.productoEscalar(_bv2), _bv0);
    EXPECT_EQ(_bv2.productoEscalar(_bv0), _bv0);
    EXPECT_EQ(_bv0.productoEscalar(_bv0), _bv0);
    EXPECT_EQ(_bv2.productoEscalar(_bv3), _bv0);
    EXPECT_EQ(_bv3.productoEscalar(_bv2), _bv0);
    ASSERT_NE(_bv2.productoEscalar(_bv2), _bv0);
    EXPECT_EQ(_bv2.productoEscalar(_bv2), _bv2squared);

    EXPECT_EQ(_bv0.productoEscalar(_bv1), _bv0);
    EXPECT_EQ(_bv1.productoEscalar(_bv1), _bv1);
    EXPECT_EQ(_bv2.productoEscalar(_bv1), _bv2);
    EXPECT_EQ(_bv1.productoEscalar(_bv2), _bv2);
    EXPECT_EQ(_bv1.productoEscalar(_bv3), _bv3);
    EXPECT_EQ(_bv3.productoEscalar(_bv1), _bv3);
}

TEST_F(TestAplicaciones01, BigVector_suma) {
    EXPECT_EQ(_bv0.suma(_bv0), _bv0);
    EXPECT_EQ(_bv0.suma(_bv1), _bv1);
    EXPECT_EQ(_bv0.suma(_bv2), _bv2);
    EXPECT_EQ(_bv0.suma(_bv3), _bv3);

    EXPECT_EQ(_bv1.suma(_bv0), _bv1);
    EXPECT_EQ(_bv2.suma(_bv0), _bv2);
    EXPECT_EQ(_bv3.suma(_bv0), _bv3);

    EXPECT_EQ(_bv2.suma(_bv3), _bv2pbv3);
    EXPECT_EQ(_bv3.suma(_bv2), _bv2pbv3);

    EXPECT_EQ(_bv2.suma(_bv2), _bv2twice);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}