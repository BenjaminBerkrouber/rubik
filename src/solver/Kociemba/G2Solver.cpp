#include "../../../include/solver/Kociemba/G2Solver.hpp"


G2Solver::G2Solver() : _spinManager() {
    // pruning::io::load("g1_corners_edges.prune", _pruningOrientation, 0x01);
    // pruning::io::load("g1_Mslice.prune", _pruningMSlice, 0x02);
}


bool G2Solver::areInverseMoves(SpinLst a, SpinLst b) {
    int faceA = static_cast<int>(a) / 3;
    int faceB = static_cast<int>(b) / 3;

    if (faceA != faceB) return false;

    int turnA = static_cast<int>(a) % 3;
    int turnB = static_cast<int>(b) % 3;
    return (turnA + turnB) == 3;
}

#include <iostream>

bool G2Solver::IDA(
    CubeState state,
    int maxDepth,
    int depth,
    bool hasLastMove,
    SpinLst lastMove
) {

    // size_t indexOrient = encodeOrientationIndex(state);
    // size_t indexMSlice = encodeMSlice(state);

    // uint8_t heuristic = std::max(_pruningOrientation[indexOrient], _pruningMSlice[indexMSlice]);
    uint8_t heuristic = 0;
    // if (heuristic == 0) return true;
    if (depth == 10 ) return false; // 8 is the max depth for G2 REMOVE THIS LINE
    if (state.isSolved()) return true;
    if (depth + heuristic > maxDepth) return false;

    for (SpinLst move : _allowSpin) {
        if (hasLastMove && areInverseMoves(lastMove, move)) continue;

        CubeState next = state;
        _spinManager.applyMove(next, move);
        _solution.push_back(move);

        if (IDA(next, maxDepth, depth + 1, true, move)) {
            return true;
        }

        _solution.pop_back();
    }

    return false;
}



bool G2Solver::solve(CubeState &state) {
    for (int depth = 0; depth <= 12; ++depth) {
        _solution.clear();
        if (IDA(state, depth)) return true;
    }
    return false;
}

std::vector<SpinLst> G2Solver::getSolution() const {
    return _solution;
}