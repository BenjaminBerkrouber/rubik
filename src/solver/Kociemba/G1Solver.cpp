#include "../../../include/solver/Kociemba/G1Solver.hpp"


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================

#include <iostream>


G1Solver::G1Solver() : _spinManager() {
    pruning::io::load("./table/Kociemba/g1_corners_edges.prune", _pruningOrientation, 0x01);
    pruning::io::load("./table/Kociemba/g1_Mslice.prune", _pruningMSlice, 0x02);
    p1Tables_ = MoveTables::load("./table/Kociemba/g1_moves.bin");
}


// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================

inline int axisOf(SpinLst m) {
    static constexpr int FACE_TO_AXIS[6] = {0, 0, 2, 2, 1, 1};
    int face = static_cast<int>(m) / 3;
    return FACE_TO_AXIS[face];
}

bool G1Solver::IDA(
    const P1State& s,
    int g,
    int bound,
    bool hasLastMove,
    SpinLst lastMove
) {
    uint8_t h = std::max(
        _pruningOrientation[s.twist * 2048 + s.flip],
        _pruningMSlice[s.mslice]
    );
    int f = g + h;
    if (f > bound) return false;
    if (h == 0)    return true;

    for (int moveInt = 0; moveInt < SPIN_COUNT; ++moveInt) {
        SpinLst move = static_cast<SpinLst>(moveInt);
        
        if (_mode) {
            auto faceOf = [](SpinLst x){ return static_cast<int>(x) / 3; };
            if (hasLastMove && faceOf(lastMove) == faceOf(move)) continue;
        } else {
            if (hasLastMove && axisOf(lastMove) == axisOf(move)) continue;
        }

        P1State n{
            p1Tables_.nextTwist (s.twist , moveInt),
            p1Tables_.nextFlip  (s.flip  , moveInt),
            p1Tables_.nextMSlice(s.mslice, moveInt)
        };

        _solution.push_back(move);
        if (IDA(n, g + 1, bound, true, move)) return true;
        _solution.pop_back();
    }
    return false;
}



bool G1Solver::solve(CubeState& state, bool mode) {
    _mode = mode;
    P1State root{
        (uint16_t)encodeCornersOrientation(state),
        (uint16_t)encodeEdgesOrientation(state),
        (uint16_t)encodeMSlice(state)
    };
    int bound = std::max(
        _pruningOrientation[root.twist * 2048 + root.flip],
        _pruningMSlice[root.mslice]
    );

    for (int depth = bound; depth <= 20; ++depth) {
        _solution.clear();
        if (IDA(root, 0, depth, false, (SpinLst)0))
            return true;
    }
    return false;
}


// ==============================================================================================================================
// ==== Utils Method ====
// ==============================================================================================================================


bool G1Solver::checkTable() const {
    if (p1Tables_.twist_.empty() || 
        p1Tables_.flip_.empty()  || 
        p1Tables_.mslice_.empty()) {
        return false;
    }
    
    return (_pruningOrientation.size() == 2048 * 2187 && 
            _pruningMSlice.size() == 495);
}

// ====================================================================================
// ==== Getter ====
// ====================================================================================


std::vector<SpinLst> G1Solver::getSolution() const {
    return _solution;
}