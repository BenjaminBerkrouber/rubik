#include "../../include/Cube.hpp"
#include "../../include/SpinLib.hpp"
#include <gtest/gtest.h>


class SpinDTest : public ::testing::Test {
    protected:
        Cube cube;
        void SetUp() override {
        }

        void TearDown() override {
            // Cleanup if necessary
        }
};


/* ============================================================================
 * ==== Spin D Tests
============================================================================= */

    TEST_F(SpinDTest, SpinD) {
        cube.applySpin(SpinId::D);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 7, 4, 5, 6}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 11, 8, 9, 10}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinDTest, SpinD_Two) {
        cube.applySpin(SpinId::D);
        cube.applySpin(SpinId::D);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 6, 7, 4, 5}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 8, 9}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinDTest, SpinD_rotate) {
        cube.applySpin(SpinId::D);
        cube.applySpin(SpinId::D);
        cube.applySpin(SpinId::D);
        cube.applySpin(SpinId::D);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

        // TEST_F(SpinDTest, SpinD_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::L);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::D);  
        //     cube.applySpin(SpinId::D);

        //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin D_PRIME Tests
============================================================================= */


    TEST_F(SpinDTest, SpinD_PRIME) {
        cube.applySpin(SpinId::D_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 5, 6, 7, 4}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 8}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinDTest, SpinD_PRIME_Two) {
        cube.applySpin(SpinId::D_PRIME);
        cube.applySpin(SpinId::D_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 6, 7, 4, 5}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 8, 9}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinDTest, SpinD_PRIME_rotate) {
        cube.applySpin(SpinId::D_PRIME);
        cube.applySpin(SpinId::D_PRIME);
        cube.applySpin(SpinId::D_PRIME);
        cube.applySpin(SpinId::D_PRIME);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

        // TEST_F(SpinDTest, SpinD_PRIME_unordoned) {
        //     cube.applySpin(SpinId::R);
        //     cube.applySpin(SpinId::F);
        //     cube.applySpin(SpinId::L);
        //     cube.applySpin(SpinId::F2);

        //     cube.applySpin(SpinId::D_PRIME);  
        //     cube.applySpin(SpinId::D_PRIME);

        // EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
        // EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
        //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
        //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
        // }

/* ============================================================================
 * ==== Spin D2 Tests
============================================================================= */

    TEST_F(SpinDTest, SpinD2) {
        cube.applySpin(SpinId::D2);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 6, 7, 4, 5}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 8, 9}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }

    TEST_F(SpinDTest, SpinD2_rotate) {
        cube.applySpin(SpinId::D2);
        cube.applySpin(SpinId::D2);

        EXPECT_EQ(cube.getCorners(), (std::array<uint8_t, 8>{0, 1, 2, 3, 4, 5, 6, 7}));
        EXPECT_EQ(cube.getEdges(), (std::array<uint8_t, 12>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}));
        EXPECT_EQ(cube.getCornerOrientations(), (std::array<uint8_t, 8>{0, 0, 0, 0, 0, 0, 0, 0}));
        EXPECT_EQ(cube.getEdgeOrientations(), (std::array<uint8_t, 12>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    }


    // TEST_F(SpinDTest, SpinD2_unordoned) {
    //     cube.applySpin(SpinId::R);
    //     cube.applySpin(SpinId::F);
    //     cube.applySpin(SpinId::L);
    //     cube.applySpin(SpinId::F2);

    //     cube.applySpin(SpinId::D2);  
    //     cube.applySpin(SpinId::D2);

    //     EXPECT_EQ(cube.getCorners(), "0 1 2 3 4 5 6 7 ");
    //     EXPECT_EQ(cube.getEdges(), "0 1 2 3 4 5 6 7 8 9 10 11 ");
    //     EXPECT_EQ(cube.getCornerOrientations(), "0 0 0 0 0 0 0 0 ");
    //     EXPECT_EQ(cube.getEdgeOrientations(), "0 0 0 0 0 0 0 0 0 0 0 0 ");
    // }
