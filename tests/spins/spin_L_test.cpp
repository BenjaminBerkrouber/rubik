#include "../../include/Cube.hpp"
#include "../../include/SpinLib.hpp"
#include <gtest/gtest.h>


class SpinLTest : public ::testing::Test {
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
 * ==== Spin L Tests
============================================================================= */

    TEST_F(SpinLTest, SpinL) {
        cube.applySpin(SpinId::L);

        EXPECT_EQ(cube.getCorners(), "0 2 6 3 4 1 5 7 ");
        EXPECT_EQ(cube.getEdges(), "0 6 2 3 4 1 9 7 8 5 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 2 1 0 0 1 2 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinLTest, SpinL_Two) {
        cube.applySpin(SpinId::L);
        cube.applySpin(SpinId::L);

        EXPECT_EQ(cube.getCorners(), "0 6 5 3 4 2 1 7 ");
        EXPECT_EQ(cube.getEdges(), "0 9 2 3 4 6 5 7 8 1 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinLTest, SpinL_rotate) {
        cube.applySpin(SpinId::L);
        cube.applySpin(SpinId::L);
        cube.applySpin(SpinId::L);
        cube.applySpin(SpinId::L);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

        // TEST_F(SpinLTest, SpinL_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::L);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::L);  
        //     cube.applySpin(SpinId::L);

        // EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        // EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin L_PRIME Tests
============================================================================= */

    TEST_F(SpinLTest, SpinL_PRIM) {
        cube.applySpin(SpinId::L_PRIME);

        EXPECT_EQ(cube.getCorners(), "0 5 1 3 4 6 2 7 ");
        EXPECT_EQ(cube.getEdges(), "0 5 2 3 4 9 1 7 8 6 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 2 1 0 0 1 2 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinLTest, SpinL_PRIM_Two) {
        cube.applySpin(SpinId::L_PRIME);
        cube.applySpin(SpinId::L_PRIME);

        EXPECT_EQ(cube.getCorners(), "0 6 5 3 4 2 1 7 ");
        EXPECT_EQ(cube.getEdges(), "0 9 2 3 4 6 5 7 8 1 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinLTest, SpinL_PRIM_rotate) {
        cube.applySpin(SpinId::L_PRIME);
        cube.applySpin(SpinId::L_PRIME);
        cube.applySpin(SpinId::L_PRIME);
        cube.applySpin(SpinId::L_PRIME);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

        // TEST_F(SpinLTest, SpinL_PRIM_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::L);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::L_PRIME);  
        //     cube.applySpin(SpinId::L_PRIME);

        //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin L2 Tests
============================================================================= */

    TEST_F(SpinLTest, SpinL2) {
        cube.applySpin(SpinId::L2);

        EXPECT_EQ(cube.getCorners(), "0 6 5 3 4 2 1 7 ");
        EXPECT_EQ(cube.getEdges(), "0 9 2 3 4 6 5 7 8 1 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinLTest, SpinL2_rotate) {
        cube.applySpin(SpinId::L2);
        cube.applySpin(SpinId::L2);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }


    // TEST_F(SpinLTest, SpinL2_unordoned) {
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::L);
    //     cube.applySpin(SpinId::F2);

    //     cube.applySpin(SpinId::L2);  
    //     cube.applySpin(SpinId::L2);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }
