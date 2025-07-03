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
    EXPECT_EQ(spin.cornersMoves[0].from, 0);
    EXPECT_EQ(spin.cornersMoves[0].to, 1);
    EXPECT_EQ(spin.edgesMoves[0].from, 0);
    EXPECT_EQ(spin.edgesMoves[0].to, 1);
}

TEST(SpinLibTest, GetSpinInvalidIdThrows) {
    SpinLib& lib = SpinLib::getInstance();
    EXPECT_THROW(lib.getSpin(static_cast<SpinId>(static_cast<uint8_t>(SpinId::COUNT))), std::out_of_range);
}

