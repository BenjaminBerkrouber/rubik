#include "../../include/Cube.hpp"
#include "../../include/SpinLib.hpp"
#include <gtest/gtest.h>


class SpinUTest : public ::testing::Test {
    protected:
        Cube cube;
        void SetUp() override {
        }

        void TearDown() override {
            // Cleanup if necessary
        }
};


/* ============================================================================
 * ==== Spin U Tests
============================================================================= */

    TEST_F(SpinUTest, SpinU) {
        cube.applySpin(SpinId::U);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{3, 0, 1, 2, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{3, 0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinUTest, SpinU_Two) {
        cube.applySpin(SpinId::U);
        cube.applySpin(SpinId::U);
        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{2, 3, 0, 1, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinUTest, SpinU_rotate) {
        cube.applySpin(SpinId::U);
        cube.applySpin(SpinId::U);
        cube.applySpin(SpinId::U);
        cube.applySpin(SpinId::U);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    // TEST_F(SpinUTest, SpinU_unordoned) {
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::L);
    //     cube.applySpin(SpinId::F2);

    //     cube.applySpin(SpinId::U);  
    //     cube.applySpin(SpinId::U);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }

/* ============================================================================
 * ==== Spin U_PRIME Tests
============================================================================= */


    TEST_F(SpinUTest, SpinU_PRIME) {
        cube.applySpin(SpinId::U_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{1, 2, 3, 0, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{1, 2, 3, 0, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinUTest, SpinU_PRIME_Two) {
        cube.applySpin(SpinId::U_PRIME);
        cube.applySpin(SpinId::U_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{2, 3, 0, 1, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinUTest, SpinU_PRIME_rotate) {
        cube.applySpin(SpinId::U_PRIME);
        cube.applySpin(SpinId::U_PRIME);
        cube.applySpin(SpinId::U_PRIME);
        cube.applySpin(SpinId::U_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

        // TEST_F(SpinUTest, SpinU_PRIME_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::L);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::U_PRIME);  
        //     cube.applySpin(SpinId::U_PRIME);

        //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin U2 Tests
============================================================================= */

    TEST_F(SpinUTest, SpinU2) {
        cube.applySpin(SpinId::U2);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{2, 3, 0, 1, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{2, 3, 0, 1, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinUTest, SpinU2_rotate) {
        cube.applySpin(SpinId::U2);
        cube.applySpin(SpinId::U2);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }


    // TEST_F(SpinUTest, SpinU2_unordoned) {
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::L);
    //     cube.applySpin(SpinId::F2);

    //     cube.applySpin(SpinId::U2);  
    //     cube.applySpin(SpinId::U2);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }
