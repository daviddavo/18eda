#include "gtest/gtest.h"
#include "sol.h"
#include "Arbin.h"

class TestArbolPerdidasGanancias : public ::testing::Test {
    protected:
    Arbin<int> a0_;
    Arbin<int> a1_;
    Arbin<int> a2_;

    void SetUp() override {
        a1_ = Arbin<int>(
            Arbin<int>(
                Arbin<int>(),
                -9,
                Arbin<int>(100)
            ),
            5,
            Arbin<int>(
                Arbin<int>(),
                -4,
                Arbin<int>(3)
            )
        );

        a2_ = Arbin<int>(
            Arbin<int>(
                Arbin<int>(5),
                -2,
                Arbin<int>(6)
            ),
            2,
            Arbin<int>(
                Arbin<int>(),
                -1,
                Arbin<int>(-1)
            )
        );
    }
};

TEST_F(TestArbolPerdidasGanancias, Everything) {
    bool rentable;
    int renta_maxima;
    mejor_renta(a0_, rentable, renta_maxima);
    EXPECT_FALSE(rentable);
    mejor_renta(a1_, rentable, renta_maxima);
    EXPECT_TRUE(rentable);
    EXPECT_EQ(renta_maxima, 4);
    mejor_renta(a2_, rentable, renta_maxima);
    EXPECT_FALSE(rentable);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}