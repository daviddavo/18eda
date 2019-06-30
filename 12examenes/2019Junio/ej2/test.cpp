#include "gtest/gtest.h"
#include "sol.h"
#include "Arbin.h"

typedef struct {
    Arbin<int> a;
    bool r;
    int m;
} tExpected;

class TestArbolPerdidasGanancias : public ::testing::TestWithParam<tExpected> {};

INSTANTIATE_TEST_SUITE_P(ITestPG, TestArbolPerdidasGanancias, ::testing::Values(
    tExpected {
        Arbin<int>(),
        false,
        -3
    },
    tExpected {
        Arbin<int>(
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
        ),
        true,
        4
    },
    tExpected {
        Arbin<int>(
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
        ),
        false,
        9142149
    },
    tExpected {
        Arbin<int>(5),
        true,
        5
    }
));

TEST_P(TestArbolPerdidasGanancias, Everything) {
    bool rentable;
    int renta_maxima;
    tExpected exp = GetParam();
    mejor_renta(exp.a, rentable, renta_maxima);
    EXPECT_EQ(exp.r, rentable);
    if (rentable && exp.r) 
        EXPECT_EQ(exp.m, renta_maxima);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}