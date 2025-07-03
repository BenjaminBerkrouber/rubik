#include <gtest/gtest.h>
#include "../include/SpinLib.hpp"

TEST(SpinLibTest, SingletonReturnsSameInstance) {
    SpinLib& lib1 = SpinLib::getInstance();
    SpinLib& lib2 = SpinLib::getInstance();
    EXPECT_EQ(&lib1, &lib2);
}

TEST(SpinLibTest, GetSpinValidId) {
    SpinLib& lib = SpinLib::getInstance();
    const Spin& spin = lib.getSpin(SpinId::U);
    EXPECT_EQ(spin.cornersMoves[0].index, 0);
    EXPECT_EQ(spin.edgesMoves[0].index, 0);
}


