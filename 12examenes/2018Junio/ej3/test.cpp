#include "gtest/gtest.h"
#include "ParqueNatural.h"

class TestParquesNaturales : public ::  testing::Test {
    protected:
    ParqueNatural _pn0;
    ParqueNatural _pn1;

    Lista<tEspecie> _pn1lista;
    Lista<tEspecie> _egqetyaLista;

    void SetUp() override {
        _pn1.an_ecosistema("test");
        _pn1.an_ecosistema("elgatoqueestatristeyazul");
        _pn1.an_ecosistema("ecosistemavacio");

        _pn1.an_ejemplares("test", "gato", 5);
        _pn1.an_ejemplares("test", "perro", 2);
        _pn1.an_ejemplares("elgatoqueestatristeyazul", "gato", 1);

        _egqetyaLista.pon_final("gato");

        _pn1lista.pon_final("gato");
        _pn1lista.pon_final("perro");
    }
};

TEST_F(TestParquesNaturales, AnadirEcosistema) {
    EXPECT_THROW(_pn1.an_ecosistema("test"), EEcosistemaDuplicado);
    EXPECT_NO_THROW(_pn0.an_ecosistema("test"));
}

TEST_F(TestParquesNaturales, AnadirEjemplares) {
    EXPECT_THROW(_pn0.an_ejemplares("test", "dontcare", 0), EEcosistemaNoExiste);
}

TEST_F(TestParquesNaturales, ContarEjemplaresEcosistema) {
    EXPECT_THROW(_pn0.numero_ejemplares_en_ecosistema("test", "dontcare"), EEcosistemaNoExiste);
    EXPECT_EQ(_pn1.numero_ejemplares_en_ecosistema("test", "gato"), 5);
    EXPECT_EQ(_pn1.numero_ejemplares_en_ecosistema("elgatoqueestatristeyazul", "gato"), 1);
    EXPECT_EQ(_pn1.numero_ejemplares_en_ecosistema("test", "perro"), 2);
}

TEST_F(TestParquesNaturales, ContarEjemplaresParque) {
    EXPECT_EQ(_pn0.numero_ejemplares_en_parque("gato"), 0);

    EXPECT_EQ(_pn1.numero_ejemplares_en_parque("perro"), 2);
    EXPECT_EQ(_pn1.numero_ejemplares_en_parque("gato"), 6);
    _pn1.an_ejemplares("test", "gato", 3);
    EXPECT_EQ(_pn1.numero_ejemplares_en_parque("gato"), 9);
}

TEST_F(TestParquesNaturales, ListaEjemplares) {
    EXPECT_EQ(_pn0.lista_especies_parque(), Lista<tEspecie>());
    EXPECT_EQ(_pn1.lista_especies_parque(), _pn1lista);
}

TEST_F(TestParquesNaturales, ListaEspeciesEcosistema) {
    EXPECT_THROW(_pn0.lista_especies_ecosistema("test", 5), EEcosistemaNoExiste);
    EXPECT_EQ(_pn1.lista_especies_ecosistema("ecosistemavacio", 5), Lista<tEspecie>());
    EXPECT_EQ(_pn1.lista_especies_ecosistema("test", 0), Lista<tEspecie>());
    EXPECT_EQ(_pn1.lista_especies_ecosistema("test", 1), _egqetyaLista);
    EXPECT_EQ(_pn1.lista_especies_ecosistema("test", 2), _pn1lista);
    EXPECT_EQ(_pn1.lista_especies_ecosistema("test", 3), _pn1lista);
    EXPECT_EQ(_pn1.lista_especies_ecosistema("elgatoqueestatristeyazul", 1), _egqetyaLista);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}