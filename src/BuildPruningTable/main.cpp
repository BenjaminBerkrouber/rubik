#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../../include/cube/Encoding.h"
#include "../../include/spin/SpinManager.hpp"
#include "../../include/solver/Kociemba/G1Solver.hpp"
#include "../../include/solver/Kociemba/G2Solver.hpp"
#include "../../include/solver/Pruning/TableIO.hpp"
#include "../../include/BuildPruningTable/TableGenerator.hpp"



// ______________________________________________ G1 ______________________________________________


void KociembagenerateG1PruningOrientation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Kociemba/g1_corners_edges.prune", table, 0x01))
        return;

    auto newTable = TableGenerator::generate(
        encodeOrientationIndex,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        2048 * 2187
    );
    pruning::io::save("./table/Kociemba/g1_corners_edges.prune", newTable, 0x01);
}

void KociembagenerateG1PruningMSlice() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Kociemba/g1_Mslice.prune", table, 0x02))
        return;

    auto newTable = TableGenerator::generate(
        encodeMSlice,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        495
    );
    pruning::io::save("./table/Kociemba/g1_Mslice.prune", newTable, 0x02);
}


// ______________________________________________ G2 ______________________________________________

void KociembagenerateG2CornersPermutation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Kociemba/g2_corners_permutation.prune", table, 0x01))
        return;

    auto newTable = TableGenerator::generate(
        encodeCornerPermutation,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        40320, // 8! permutations
        {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
        }
    );
    pruning::io::save("./table/Kociemba/g2_corners_permutation.prune", newTable, 0x01);
}


void KociembagenerateG2UDSlicePermutation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Kociemba/g2_uDSlice_permutation.prune", table, 0x01))
        return;

    auto newTable = TableGenerator::generate(
        encodeUDSlicePermutation,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        40320, // 8! permutations
        {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
        }
    );
    pruning::io::save("./table/Kociemba/g2_uDSlice_permutation.prune", newTable, 0x01);
}

void KociembagenerateG2MSlicePermutation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Kociemba/g2_mSLice_permutation.prune", table, 0x01))
        return;
    auto newTable = TableGenerator::generate(
        encodeMSliceEdgePermutation,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        24, // 4! permutations
        {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
        }
    );
    pruning::io::save("./table/Kociemba/g2_mSLice_permutation.prune", newTable, 0x01);
}

void ThistlethwaiteG1Pruning() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Thistlethwaite/g1_edge_orientation.prune", table, 0x01))
        return;
    auto newTable = TableGenerator::generate(
        encodeEdgesOrientation,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        2048 // 2^11 orientations
    );
    pruning::io::save("./table/Thistlethwaite/g1_edge_orientation.prune", newTable, 0x01);
}

void ThistlethwaiteG2Pruning() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Thistlethwaite/g2_corner_orientation_mSlice.prune", table, 0x01))
        return;
    auto newTable = TableGenerator::generate(
        encodageG2,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        2187 * 495, // 3^7 * C(12, 4) = 1081065
        {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L, SpinLst::L2, SpinLst::L3,
            SpinLst::R, SpinLst::R2, SpinLst::R3,
            SpinLst::F2, SpinLst::B2
        }
    );
    pruning::io::save("./table/Thistlethwaite/g2_corner_orientation_mSlice.prune", newTable, 0x01);
}


void ThistlethwaiteG3Pruning() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Thistlethwaite/g3_group_edgeCornes_parity.prune", table, 0x01))
        return;
    auto newTable = TableGenerator::generate(
        encodeG3,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        29400,
        {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
        }
    );
    pruning::io::save("./table/Thistlethwaite/g3_group_edgeCornes_parity.prune", newTable, 0x01);
}

void ThistlethwaiteG4Pruning() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/Thistlethwaite/g4_mirrorSpin.prune", table, 0x01))
        return;
    auto newTable = TableGenerator::generate(
        encodeG4,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        18501, // (4!^5/12)
        {
            SpinLst::U2, SpinLst::D2, SpinLst::L2, 
            SpinLst::R2, SpinLst::F2, SpinLst::B2
        }
    );
    pruning::io::save("./table/Thistlethwaite/g4_mirrorSpin.prune", newTable, 0x01);
}


int main() {

    // Kociemba Pruning Tables Generation
    // G1
    KociembagenerateG1PruningOrientation();
    KociembagenerateG1PruningMSlice();

    // G2
    KociembagenerateG2CornersPermutation();
    KociembagenerateG2UDSlicePermutation();
    KociembagenerateG2MSlicePermutation();
    std::cout << "Kociemba Pruning Tables Generated Successfully!" << std::endl;

    // Thistlethwaite Pruning Tables Generation
    ThistlethwaiteG1Pruning();
    ThistlethwaiteG2Pruning();
    ThistlethwaiteG3Pruning();
    ThistlethwaiteG4Pruning();
    std::cout << "Thistlethwaite Pruning Tables Generated Successfully!" << std::endl;
    return 0;
}