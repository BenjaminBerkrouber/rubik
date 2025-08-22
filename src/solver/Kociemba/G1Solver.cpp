#include "../../../include/solver/Kociemba/G1Solver.hpp"


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


G1Solver::G1Solver() : _spinManager() {
    pruning::io::load("./table/Kociemba/g1_corners_edges.prune", _pruningOrientation, 0x01);
    pruning::io::load("./table/Kociemba/g1_Mslice.prune", _pruningMSlice, 0x02);
}


// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================


bool G1Solver::IDA(
    CubeState state,
    int maxDepth,
    int depth,
    bool hasLastMove,
    SpinLst lastMove
) {

    size_t indexOrient = encodeOrientationIndex(state);
    size_t indexMSlice = encodeMSlice(state);

    uint8_t heuristic = std::max(_pruningOrientation[indexOrient], _pruningMSlice[indexMSlice]);

    if (heuristic == 0) return true;
    if (depth + heuristic > maxDepth) return false;

    for (int moveInt = 0; moveInt < SPIN_COUNT; ++moveInt) {
        SpinLst move = static_cast<SpinLst>(moveInt);
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



bool G1Solver::solve(CubeState &state) {
    for (int depth = 0; depth <= 20; ++depth) {
        _solution.clear();
        if (IDA(state, depth)) return true;
    }
    return false;
}


// ==============================================================================================================================
// ==== Utils Method ====
// ==============================================================================================================================


bool G1Solver::checkTable() const {
    return (_pruningOrientation.size() == 2048 * 2187 && 
            _pruningMSlice.size() == 495);
}

bool G1Solver::areInverseMoves(SpinLst a, SpinLst b) {
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


std::vector<SpinLst> G1Solver::getSolution() const {
    return _solution;
}