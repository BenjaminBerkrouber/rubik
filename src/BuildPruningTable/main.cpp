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


void generateG1PruningOrientation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/g1_corners_edges.prune", table, 0x01))
        return;

    auto newTable = TableGenerator::generate(
        encodeOrientationIndex,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        2048 * 2187
    );
    pruning::io::save("./table/g1_corners_edges.prune", newTable, 0x01);
}

void generateG1PruningMSlice() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/g1_Mslice.prune", table, 0x02))
        return;

    auto newTable = TableGenerator::generate(
        encodeMSlice,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        495
    );
    pruning::io::save("./table/g1_Mslice.prune", newTable, 0x02);
}


// ______________________________________________ G2 ______________________________________________

void generateG2CornersPermutation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/g2_corners_permutation.prune", table, 0x01))
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
    pruning::io::save("./table/g2_corners_permutation.prune", newTable, 0x01);
}


void generateG2UDSlicePermutation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/g2_uDSlice_permutation.prune", table, 0x01))
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
    pruning::io::save("./table/g2_uDSlice_permutation.prune", newTable, 0x01);
}

void generateG2MSlicePermutation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("./table/g2_mSLice_permutation.prune", table, 0x01))
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
    pruning::io::save("./table/g2_mSLice_permutation.prune", newTable, 0x01);
}


int main() {
    // G1
    generateG1PruningOrientation();
    generateG1PruningMSlice();

    // G2
    generateG2CornersPermutation();
    generateG2UDSlicePermutation();
    generateG2MSlicePermutation();
    std::cout << "✅ Pruning tables generated successfully.\n"; 
    return 0;
}