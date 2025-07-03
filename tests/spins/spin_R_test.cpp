#include "../../include/Cube.hpp"
#include "../../include/SpinLib.hpp"
#include <gtest/gtest.h>


class SpinRTest : public ::testing::Test {
    protected:
        Cube cube;
        void SetUp() override {
            cube = Cube();
        }

        void TearDown() override {
            // Cleanup if necessary
        }
};


/* ============================================================================
 * ==== Spin R Tests
============================================================================= */

    TEST_F(SpinRTest, SpinR) {
        cube.applySpin(SpinId::R);

        EXPECT_EQ(cube.getCorners(), "4 1 2 0 7 5 6 3 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 4 11 5 6 3 8 9 10 7 ");
        EXPECT_EQ(cube.getCornerOrientations(), "1 0 0 2 2 0 0 1 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinRTest, SpinR_Two) {
        cube.applySpin(SpinId::R);
        cube.applySpin(SpinId::R);

        EXPECT_EQ(cube.getCorners(), "7 1 2 4 3 5 6 0 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 11 7 5 6 4 8 9 10 3 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinRTest, SpinR_rotate) {
        cube.applySpin(SpinId::R);
        cube.applySpin(SpinId::R);
        cube.applySpin(SpinId::R);
        cube.applySpin(SpinId::R);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

        // TEST_F(SpinRTest, SpinR_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::R2);

        //     cube.applySpin(SpinId::R);  
        //     cube.applySpin(SpinId::R);

        // EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        // EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin R_PRIME Tests
============================================================================= */

    TEST_F(SpinRTest, SpinR_PRIM) {
        cube.applySpin(SpinId::R_PRIME);

        EXPECT_EQ(cube.getCorners(), "3 1 2 7 0 5 6 4 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 7 3 5 6 11 8 9 10 4 ");
        EXPECT_EQ(cube.getCornerOrientations(), "1 0 0 2 2 0 0 1 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinRTest, SpinR_PRIM_Two) {
        cube.applySpin(SpinId::R_PRIME);
        cube.applySpin(SpinId::R_PRIME);

        EXPECT_EQ(cube.getCorners(), "7 1 2 4 3 5 6 0 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 11 7 5 6 4 8 9 10 3 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinRTest, SpinR_PRIM_rotate) {
        cube.applySpin(SpinId::R_PRIME);
        cube.applySpin(SpinId::R_PRIME);
        cube.applySpin(SpinId::R_PRIME);
        cube.applySpin(SpinId::R_PRIME);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

        // TEST_F(SpinRTest, SpinR_PRIM_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::R2);

        //     cube.applySpin(SpinId::R_PRIME);  
        //     cube.applySpin(SpinId::R_PRIME);

        //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin R2 Tests
============================================================================= */

    TEST_F(SpinRTest, SpinR2) {
        cube.applySpin(SpinId::R2);

        EXPECT_EQ(cube.getCorners(), "7 1 2 4 3 5 6 0 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 11 7 5 6 4 8 9 10 3 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinRTest, SpinR2_rotate) {
        cube.applySpin(SpinId::R2);
        cube.applySpin(SpinId::R2);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }


    // TEST_F(SpinRTest, SpinR2_unordoned) {
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::R2);

    //     cube.applySpin(SpinId::R2);  
    //     cube.applySpin(SpinId::R2);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }
