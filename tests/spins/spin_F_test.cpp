#include "../../include/Cube.hpp"
#include "../../include/SpinLib.hpp"
#include <gtest/gtest.h>


class SpinFTest : public ::testing::Test {
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
 * ==== Spin F Tests
============================================================================= */

    TEST_F(SpinFTest, SpinF) {
        cube.applySpin(SpinId::F);

        EXPECT_EQ(cube.getCorners(), "1 5 2 3 0 4 6 7 ");
        EXPECT_EQ(cube.getEdges(), "5 1 2 3 0 8 6 7 4 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "2 1 0 0 1 2 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "1 0 0 0 1 1 0 0 1 0 0 0 ");
    }

    TEST_F(SpinFTest, SpinF_Two) {
        cube.applySpin(SpinId::F);
        cube.applySpin(SpinId::F);

        EXPECT_EQ(cube.getCorners(), "5 4 2 3 1 0 6 7 ");
        EXPECT_EQ(cube.getEdges(), "8 1 2 3 5 4 6 7 0 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinFTest, SpinF_rotate) {
        cube.applySpin(SpinId::F);
        cube.applySpin(SpinId::F);
        cube.applySpin(SpinId::F);
        cube.applySpin(SpinId::F);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

        // TEST_F(SpinFTest, SpinF_unordoned) {
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::F);  
        //     cube.applySpin(SpinId::F);

        // EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        // EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin F_PRIME Tests
============================================================================= */

    TEST_F(SpinFTest, SpinF_PRIM) {
        cube.applySpin(SpinId::F_PRIME);

        EXPECT_EQ(cube.getCorners(), "4 0 2 3 5 1 6 7 ");
        EXPECT_EQ(cube.getEdges(), "4 1 2 3 8 0 6 7 5 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "2 1 0 0 1 2 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "1 0 0 0 1 1 0 0 1 0 0 0 ");
    }

    TEST_F(SpinFTest, SpinF_PRIM_Two) {
        cube.applySpin(SpinId::F_PRIME);
        cube.applySpin(SpinId::F_PRIME);

        EXPECT_EQ(cube.getCorners(), "5 4 2 3 1 0 6 7 ");
        EXPECT_EQ(cube.getEdges(), "8 1 2 3 5 4 6 7 0 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinFTest, SpinF_PRIM_rotate) {
        cube.applySpin(SpinId::F_PRIME);
        cube.applySpin(SpinId::F_PRIME);
        cube.applySpin(SpinId::F_PRIME);
        cube.applySpin(SpinId::F_PRIME);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

        // TEST_F(SpinFTest, SpinF_PRIM_unordoned) {
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::F_PRIME);  
        //     cube.applySpin(SpinId::F_PRIME);

        //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin F2 Tests
============================================================================= */

    TEST_F(SpinFTest, SpinF2) {
        cube.applySpin(SpinId::F2);

        EXPECT_EQ(cube.getCorners(), "5 4 2 3 1 0 6 7 ");
        EXPECT_EQ(cube.getEdges(), "8 1 2 3 5 4 6 7 0 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }

    TEST_F(SpinFTest, SpinF2_rotate) {
        cube.applySpin(SpinId::F2);
        cube.applySpin(SpinId::F2);

        EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    }


    // TEST_F(SpinFTest, SpinF2_unordoned) {
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::F2);

    //     cube.applySpin(SpinId::F2);  
    //     cube.applySpin(SpinId::F2);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }
