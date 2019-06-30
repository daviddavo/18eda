#include "gtest/gtest.h"
#include "SistemaVentas.h"

class TestVentas : public ::testing::Test {
    protected:
    SistemaVentas _sv0;
    SistemaVentas _sv1;

    void SetUp() override {
        _sv1.an_oferta("lapiz", 3);
        _sv1.an_oferta("boligrafo", 5);
        _sv1.pon_en_espera("Pedro", "lapiz");
    }
};

TEST_F(TestVentas, AnOferta) {
    EXPECT_THROW(_sv1.an_oferta("lapiz", 2), EErrorAltaProducto);
    EXPECT_THROW(_sv1.an_oferta("coso", 0), EErrorAltaProducto);
    EXPECT_NO_THROW(_sv1.an_oferta("coso", 3));
}

TEST_F(TestVentas, PonEnEspera) {
    EXPECT_THROW(_sv1.pon_en_espera("Juan", "coso"), EProductoNoExiste);
    EXPECT_NO_THROW(_sv1.pon_en_espera("Pedro", "lapiz"));
}

TEST_F(TestVentas, CancelaEspera) {
    EXPECT_THROW(_sv1.cancela_espera("Juan", "coso"), EProductoNoExiste);
    EXPECT_NO_THROW(_sv1.cancela_espera("Pedro", "lapiz"));
    EXPECT_NO_THROW(_sv1.cancela_espera("Pedro", "lapiz"));
    EXPECT_NO_THROW(_sv1.cancela_espera("Juan", "lapiz"));
}

TEST_F(TestVentas, NumEnEspera) {
    EXPECT_THROW(_sv1.num_en_espera("coso"), EProductoNoExiste);
    EXPECT_EQ(_sv1.num_en_espera("lapiz"), 1);
    _sv1.pon_en_espera("Juan", "lapiz");
    EXPECT_EQ(_sv1.num_en_espera("lapiz"), 2);
    _sv1.pon_en_espera("Juan", "lapiz");
    EXPECT_EQ(_sv1.num_en_espera("lapiz"), 2);
    _sv1.cancela_espera("Juan", "lapiz");
    EXPECT_EQ(_sv1.num_en_espera("lapiz"), 1);
}

TEST_F(TestVentas, Venta) {
    EXPECT_THROW(_sv1.venta("coso", 3), EErrorVenta);
    EXPECT_THROW(_sv1.venta("lapiz", -3), EErrorVenta);
    EXPECT_THROW(_sv1.venta("lapiz", 500), EErrorVenta);
    EXPECT_THROW(_sv1.venta("boligrafo", 1), EErrorVenta);
    EXPECT_NO_THROW(_sv1.venta("lapiz", 1));
    EXPECT_EQ(_sv1.num_en_espera("lapiz"), 0);
    _sv1.pon_en_espera("Juan", "lapiz");
    EXPECT_NO_THROW(_sv1.venta("lapiz", 2));
    EXPECT_THROW(_sv1.venta("lapiz", 1), EErrorVenta);

    _sv1.an_oferta("coso", 3);
    EXPECT_THROW(_sv1.venta("coso", 1), EErrorVenta);
    
    /**
    _sv1.pon_en_espera("Juan", "coso");
    EXPECT_EQ(_sv1.num_en_espera("coso"), 1);
    _sv1.venta("coso", 0);
    EXPECT_EQ(_sv1.num_en_espera("coso"), 1);
    */
}

TEST_F(TestVentas, PrimeroEnEspera) {
    EXPECT_THROW(_sv1.primero_en_espera("coso"), EErrorAccesoListaEspera);
    EXPECT_THROW(_sv1.primero_en_espera("boligrafo"), EErrorAccesoListaEspera);
    EXPECT_EQ(_sv1.primero_en_espera("lapiz"), "Pedro");
    _sv1.venta("lapiz", 2);
    EXPECT_THROW(_sv1.primero_en_espera("lapiz"), EErrorAccesoListaEspera);
    _sv1.pon_en_espera("Juan", "boligrafo");
    _sv1.pon_en_espera("Pedro", "boligrafo");
    EXPECT_EQ(_sv1.primero_en_espera("boligrafo"), "Juan");
    _sv1.cancela_espera("Juan", "boligrafo");
    EXPECT_EQ(_sv1.primero_en_espera("boligrafo"), "Pedro");
} 

TEST_F(TestVentas, ListaVentas) {
    EXPECT_EQ(_sv0.lista_ventas(), Lista<Venta>());
    EXPECT_EQ(_sv1.lista_ventas(), Lista<Venta>());
    _sv1.venta("lapiz", 1);
    Lista<Venta> lv1;
    lv1.pon_final(Venta("lapiz", 1));
    EXPECT_EQ(_sv1.lista_ventas(), lv1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}