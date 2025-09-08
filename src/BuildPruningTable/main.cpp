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

#include "../../include/utils/Constants.hpp"
#include "../../include/utils/utils.h"
#include "../../include/spin/Spin.hpp"
#include "../../include/spin/SpinManager.hpp"
#include <array>
#include <stdexcept>
#include "../../include/solver/Kociemba/p1_move_tables.hpp"
#include "../../include/solver/Kociemba/p2_move_tables.hpp"


// =============================================================================================================================
// ==== Pruning Table for Koceimba ====
// =============================================================================================================================

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

// =============================================================================================================
// ==== Move table for Koceimba ====
// =============================================================================================================

static inline void setEdgeId(CubeState& s, int pos, uint8_t id) {
    s.edges &= ~(0xFULL << (pos*4));
    s.edges |= (uint64_t(id) & 0xFULL) << (pos*4);
}

static int binom(int n, int k) {
    if (k<0 || k>n) return 0;
    if (k==0 || k==n) return 1;
    long long r = 1;
    for (int i=1;i<=k;++i) r = r*(n-k+i)/i;
    return (int)r;
}

static std::array<uint8_t,4> unrankMSlice(uint16_t code) {
    int idx = 494 - code;
    std::array<uint8_t,4> pos{};
    int x = 11;
    for (int k = 4; k >= 1; --k) {
        while (binom(x, k) > idx) --x;
        pos[k-1] = (uint8_t)x;
        idx -= binom(x, k);
        --x;
    }
    std::sort(pos.begin(), pos.end());
    return pos;
}

void KociembageratorG1Move() {
    SpinManager spinMgr;

    MoveTables tbl = MoveTables::buildOnline(
        spinMgr,
        [](CubeState& s, uint16_t t){ decodeCornersOrientation(s, t); },
        [](CubeState& s, uint16_t f){ decodeEdgesOrientation(s, f); },
        [](CubeState& s, uint16_t m){
            auto pos = unrankMSlice(m);
            uint8_t nextNonSlice = 0;
            std::array<bool,12> isSlice{}; for (auto p : pos) isSlice[p] = true;

            for (int p = 0; p < 12; ++p)
                if (!isSlice[p]) setEdgeId(s, p, nextNonSlice++);

            for (int i = 0; i < 4; ++i) setEdgeId(s, pos[i], 8 + i);
        },
        [](const CubeState& s){ return encodeCornersOrientation(s); },
        [](const CubeState& s){ return encodeEdgesOrientation(s); },
        [](const CubeState& s){ return encodeMSlice(s); }
    );

    tbl.save("./table/Kociemba/g1_moves.bin");
}

void KociembageratorG2Move() {
    SpinManager spinMgr;

    std::vector<SpinLst> moves = {
        SpinLst::U, SpinLst::U2, SpinLst::U3,
        SpinLst::D, SpinLst::D2, SpinLst::D3,
        SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
    };

    P2MoveTables tbl = P2MoveTables::buildOnline(
        spinMgr,
        moves,
        [](CubeState& s, uint32_t c){ decodeCornerPermutation(s, c); },
        [](CubeState& s, uint32_t m){ decodeMSliceEdgePermutation(s, m); },
        [](CubeState& s, uint32_t u){ decodeUDSlicePermutation(s, u); },
        [](const CubeState& s){ return encodeCornerPermutation(s); },
        [](const CubeState& s){ return encodeMSliceEdgePermutation(s); },
        [](const CubeState& s){ return encodeUDSlicePermutation(s); }
    );

    tbl.save("./table/Kociemba/g2_moves.bin");
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

    KociembageratorG1Move();
    KociembageratorG2Move();
    std::cout << "Kociemba Move Table Generated Successfully!" << std::endl;

    return 0;
}