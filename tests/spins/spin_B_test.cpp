#include "../../include/Cube.hpp"
#include "../../include/SpinLib.hpp"
#include <gtest/gtest.h>


class SpinBTest : public ::testing::Test {
    protected:
        Cube cube;
        void SetUp() override {
        }

        void TearDown() override {
            // Cleanup if necessary
        }
};


/* ============================================================================
 * ==== Spin B Tests
============================================================================= */

    TEST_F(SpinBTest, SpinB) {
        cube.applySpin(SpinId::B);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 3, 7, 4, 5, 2, 6}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 2, 1, 0, 0, 1, 2}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0}));
    }

    TEST_F(SpinBTest, SpinB_Two) {
        cube.applySpin(SpinId::B);
        cube.applySpin(SpinId::B);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 7, 6, 4, 5, 3, 2}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 10, 3, 4, 5, 7, 6, 8, 9, 2, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinBTest, SpinB_rotate) {
        cube.applySpin(SpinId::B);
        cube.applySpin(SpinId::B);
        cube.applySpin(SpinId::B);
        cube.applySpin(SpinId::B);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

        // TEST_F(SpinBTest, SpinB_unordoned) {
        //     cube.applySpin(SpinId::B);
        //     cube.applySpin(SpinId::B);
        //     cube.applySpin(SpinId::B);
        //     cube.applySpin(SpinId::B2);

        //     cube.applySpin(SpinId::B);  
        //     cube.applySpin(SpinId::B);

        // EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        // EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin B_PRIME Tests
============================================================================= */

    TEST_F(SpinBTest, SpinB_PRIM) {
        cube.applySpin(SpinId::B_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 6, 2, 4, 5, 7, 3}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 6, 3, 4, 5, 10, 2, 8, 9, 7, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 2, 1, 0, 0, 1, 2}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0}));
    }

    TEST_F(SpinBTest, SpinB_PRIM_Two) {
        cube.applySpin(SpinId::B_PRIME);
        cube.applySpin(SpinId::B_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 7, 6, 4, 5, 3, 2}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 10, 3, 4, 5, 7, 6, 8, 9, 2, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinBTest, SpinB_PRIM_rotate) {
        cube.applySpin(SpinId::B_PRIME);
        cube.applySpin(SpinId::B_PRIME);
        cube.applySpin(SpinId::B_PRIME);
        cube.applySpin(SpinId::B_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

        // TEST_F(SpinBTest, SpinB_PRIM_unordoned) {
        //     cube.applySpin(SpinId::B);
        //     cube.applySpin(SpinId::B);
        //     cube.applySpin(SpinId::B);
        //     cube.applySpin(SpinId::B2);

        //     cube.applySpin(SpinId::B_PRIME);  
        //     cube.applySpin(SpinId::B_PRIME);

        //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin F2 Tests
============================================================================= */

    TEST_F(SpinBTest, SpinB2) {
        cube.applySpin(SpinId::B2);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 7, 6, 4, 5, 3, 2}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 10, 3, 4, 5, 7, 6, 8, 9, 2, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinBTest, SpinB2_rotate) {
        cube.applySpin(SpinId::B2);
        cube.applySpin(SpinId::B2);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }


    // TEST_F(SpinBTest, SpinB2_unordoned) {
    //     cube.applySpin(SpinId::B);
    //     cube.applySpin(SpinId::B);
    //     cube.applySpin(SpinId::B);
    //     cube.applySpin(SpinId::B2);

    //     cube.applySpin(SpinId::B2);  
    //     cube.applySpin(SpinId::B2);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }
