#include "../include/Cube.hpp"
#include "../include/SpinLib.hpp"
#include <gtest/gtest.h>


class CubeTest : public ::testing::Test {
    protected:
        Cube cube;
        void SetUp() override {
        }

        void TearDown() override {
            // Cleanup if necessary
        }
};

TEST_F(CubeTest, InitialState) {
    EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
    EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
    EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
}

TEST_F(CubeTest, SexyMove) {
    for (int i = 0; i < 6; ++i) {
        cube.applySpin(SpinId::R);
        cube.applySpin(SpinId::U);
        cube.applySpin(SpinId::R_PRIME);
        cube.applySpin(SpinId::U_PRIME);
    }

    EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
    EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
    EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
    EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
}