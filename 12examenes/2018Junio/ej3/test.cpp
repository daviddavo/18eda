#include "gtest/gtest.h"

class TestParquesNaturales : public ::  testing::Test {

};

TEST_F(TestParquesNaturales, failing) {
    EXPECT_EQ(true, false);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}