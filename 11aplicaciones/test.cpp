#include <sstream>
#include "gtest/gtest.h"

#include "01/01.h"
#include "04/04.h"

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

// https://www.embalses.net/provincia-45-madrid.html
class TestAplicaciones04 : public ::testing::Test {
    protected:
    Cuenca _c0;
    Cuenca _c1;

    void SetUp() override {
        _c1.insertar_rio("Jarama"); // Vacío siempre

        _c1.insertar_rio("Manzanares");
        _c1.insertar_pantano("Manzanares", "Navacerrada", 11, 5);
        _c1.insertar_pantano("Manzanares", "El Pardo", 43, 6);
        _c1.insertar_pantano("Manzanares", "Santillana", 91, 59);

        _c1.insertar_rio("Lozoya");
        _c1.insertar_pantano("Lozoya", "Pinilla", 38, 27);
        _c1.insertar_pantano("Lozoya", "IGN", 11, 20);  // TOO MUCH WATER
    }
};

TEST_F(TestAplicaciones04, Crear) {
    EXPECT_NO_THROW(Cuenca());
}

TEST_F(TestAplicaciones04, EmbalsadoPantano) {
    EXPECT_EQ(_c1.embalsado_pantano("Manzanares", "Navacerrada"), 5);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "Pinilla"), 27);    
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "IGN"), 11);
}

TEST_F(TestAplicaciones04, EmbalsadoCuenca) {
    EXPECT_EQ(_c1.embalsado_cuenca("Manzanares"), 5+6+59);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 38);
}

TEST_F(TestAplicaciones04, Embalsar) {
    _c1.embalsar("Lozoya", "Pinilla", 5);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "Pinilla"), 32);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 43);
    _c1.embalsar("Lozoya", "IGN", 200);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "IGN"), 11);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 43);
    _c1.embalsar("Lozoya", "Pinilla", 200000);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "Pinilla"), 38);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 49);
}

TEST_F(TestAplicaciones04, Transvasar) {
    // Transvase misma cuenca hidrografica
    _c1.transvasar("Lozoya", "Pinilla", "Lozoya", "IGN", 5);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "Pinilla"), 27);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "IGN"), 11);
    _c1.transvasar("Lozoya", "Pinilla", "Lozoya", "IGN", -5);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "Pinilla"), 32);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "IGN"), 6);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 38);

    // Transvase distinta cuenca hidrografica
    _c1.transvasar("Lozoya", "Pinilla", "Manzanares", "Santillana", 1);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "Pinilla"), 31);
    EXPECT_EQ(_c1.embalsado_pantano("Manzanares", "Santillana"), 60);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 37);
    EXPECT_EQ(_c1.embalsado_cuenca("Manzanares"), 71);

    // Transvase con más agua de la que tiene r1
    _c1.transvasar("Lozoya", "IGN", "Manzanares", "El Pardo", 10);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "IGN"), 0);
    EXPECT_EQ(_c1.embalsado_pantano("Manzanares", "El Pardo"), 12);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 31);
    EXPECT_EQ(_c1.embalsado_cuenca("Manzanares"), 77);

    // Transvase con más agua de la que soporta r2
    _c1.transvasar("Manzanares", "Santillana", "Lozoya", "IGN", 50);
    EXPECT_EQ(_c1.embalsado_pantano("Manzanares", "Santillana"), 49);
    EXPECT_EQ(_c1.embalsado_pantano("Lozoya", "IGN"), 11);
    EXPECT_EQ(_c1.embalsado_cuenca("Manzanares"), 66);
    EXPECT_EQ(_c1.embalsado_cuenca("Lozoya"), 42);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}