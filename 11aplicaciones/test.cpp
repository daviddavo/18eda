#include <sstream>
#include "gtest/gtest.h"

#include "01/01.h"

class TestAplicaciones : public :: testing::Test {};

class TestAplicaciones01 : public :: TestAplicaciones {
    protected:
    BigVector _bv0;
    BigVector _bv1;

    void SetUp() override {
        // _bv0 always 0
        for (int i = 0; i < 255; i++)
            _bv1.ponValor(i, i);
    }
};

TEST_F(TestAplicaciones01, BigVector_create) {
    ASSERT_NO_THROW(BigVector());
    for (int i = 0; i < 265; ++i)
        ASSERT_EQ(_bv0.valorDe(i), 0);
}

TEST_F(TestAplicaciones01, BigVector_ponValorValorDe) {
    for (int i = 0; i < 255; ++i)
        ASSERT_EQ(_bv1.valorDe(i), i);

    for (int i = 0; i < 5; i++)
        _bv1.ponValor(i, 0);

    for (int i = 0; i < 5; ++i)
        ASSERT_EQ(_bv1.valorDe(i), 0);
}

TEST_F(TestAplicaciones01, BigVector_productoEscalar) {
    ASSERT_EQ(_bv0.productoEscalar(_bv1), _bv0);
    ASSERT_EQ(_bv1.productoEscalar(_bv0), _bv0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}