#include "../include/Cube.hpp"
#include "../include/SpinLib.hpp"
#include <gtest/gtest.h>


class CubeTest : public ::testing::Test {
    protected:
        Cube cube;
        void SetUp() override {
            cube = Cube();
        }

        void TearDown() override {
            // Cleanup if necessary
        }
};

TEST_F(CubeTest, InitialState) {
    EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
}

TEST_F(CubeTest, SexyMove) {
    for (int i = 0; i < 6; ++i) {
        cube.applySpin(SpinId::R);
        cube.applySpin(SpinId::U);
        cube.applySpin(SpinId::R_PRIME);
        cube.applySpin(SpinId::U_PRIME);
    }

    EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
}