#include "../../../include/solver/Kociemba/G2Solver.hpp"


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


G2Solver::G2Solver() : _spinManager() {
    pruning::io::load("./table/g2_corners_permutation.prune", _pruningCornersPermutation, 0x01);
    pruning::io::load("./table/g2_mSLice_permutation.prune", _pruningMSlicePermutation, 0x01);
    pruning::io::load("./table/g2_uDSlice_permutation.prune", _pruningUDSlicePermutation, 0x01);
}


// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================


bool G2Solver::IDA(
    CubeState state,
    int maxDepth,
    std::unordered_map<CubeState, int> &visited,
    int depth,
    bool hasLastMove,
    SpinLst lastMove
) {
    size_t indexCorners = encodeCornerPermutation(state);
    size_t indexMSlice = encodeMSliceEdgePermutation(state);
    size_t indexUDSlice = encodeUDSlicePermutation(state);

    uint8_t heuristic = std::max({
        _pruningCornersPermutation[indexCorners],
        _pruningMSlicePermutation[indexMSlice],
        _pruningUDSlicePermutation[indexUDSlice]
    });

    if (heuristic == 0) return true;
    if (depth + heuristic > maxDepth) return false;

    auto it = visited.find(state);
    if (it != visited.end() && it->second <= depth) return false;
    visited[state] = depth;


    for (SpinLst move : _allowSpin) {
        if (hasLastMove && areInverseMoves(lastMove, move)) continue;

        CubeState next = state;
        _spinManager.applyMove(next, move);
        _solution.push_back(move);

        if (IDA(next, maxDepth, visited, depth + 1, true, move)) return true;

        _solution.pop_back();
    }

    return false;
}

bool G2Solver::solve(CubeState &state) {
    for (int depth = 0; depth <= 20; ++depth) {
        _solution.clear();
        std::unordered_map<CubeState, int> visited;
        if (IDA(state, depth, visited)) return true;
    }
    return false;
}


// ==============================================================================================================================
// ==== Utils Method ====
// ==============================================================================================================================


bool G2Solver::checkTable() const {
    return  (_pruningCornersPermutation.size() == 40320 &&
            _pruningMSlicePermutation.size() == 24 &&
            _pruningUDSlicePermutation.size() == 40320);
}

bool G2Solver::areInverseMoves(SpinLst a, SpinLst b) {
    int faceA = static_cast<int>(a) / 3;
    int faceB = static_cast<int>(b) / 3;

    if (faceA != faceB) return false;

    int turnA = static_cast<int>(a) % 3;
    int turnB = static_cast<int>(b) % 3;
    return (turnA + turnB) == 3;
}


// ====================================================================================
// ==== Getter ====
// ====================================================================================


std::vector<SpinLst> G2Solver::getSolution() const {
    return _solution;
}