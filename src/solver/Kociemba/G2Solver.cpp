#include "../../../include/solver/Kociemba/G2Solver.hpp"


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


G2Solver::G2Solver() : _spinManager() {
    pruning::io::load("./table/Kociemba/g2_corners_permutation.prune", _pruningCornersPermutation, 0x01);
    pruning::io::load("./table/Kociemba/g2_mSLice_permutation.prune",  _pruningMSlicePermutation,  0x01);
    pruning::io::load("./table/Kociemba/g2_uDSlice_permutation.prune", _pruningUDSlicePermutation, 0x01);
    p2Tables_ = P2MoveTables::load("./table/Kociemba/g2_moves.bin");
}



// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================


inline int axisOf(SpinLst m) {
    static constexpr int FACE_TO_AXIS[6] = {0, 0, 2, 2, 1, 1};
    int face = static_cast<int>(m) / 3;
    return FACE_TO_AXIS[face];
}


bool G2Solver::IDA(const P2State& s,
                    int g,
                    int bound,
                    bool hasLastMove,
                    SpinLst lastMove)
{
    uint8_t h = std::max({
        _pruningCornersPermutation[s.cperm],
        _pruningMSlicePermutation[s.msperm],
        _pruningUDSlicePermutation[s.udperm]
    });
    int f = g + h;
    if (f > bound) return false;
    if (h == 0)    return true;

    for (int mi = 0; mi < (int)_allowSpin.size(); ++mi) {
        SpinLst m = _allowSpin[mi];

        auto faceOf = [](SpinLst x){ return static_cast<int>(x) / 3; };
        if (hasLastMove && faceOf(lastMove) == faceOf(m)) continue;

        P2State n{
        p2Tables_.nextCorner (s.cperm , mi),
        p2Tables_.nextMSlice (s.msperm, mi),
        p2Tables_.nextUDSlice(s.udperm, mi)
        };

        _solution.push_back(m);
        if (IDA(n, g + 1, bound, true, m)) return true;
        _solution.pop_back();
    }
    return false;
}


bool G2Solver::solve(CubeState &state) {
    P2State root{
        (uint16_t)encodeCornerPermutation(state),
        (uint16_t)encodeMSliceEdgePermutation(state),
        (uint16_t)encodeUDSlicePermutation(state)
    };

    int bound = std::max({
        _pruningCornersPermutation[root.cperm],
        _pruningMSlicePermutation[root.msperm],
        _pruningUDSlicePermutation[root.udperm]
    });

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


bool G2Solver::checkTable() const {
    if (p2Tables_.corner_.empty() || 
        p2Tables_.mslice_.empty()  || 
        p2Tables_.udslc_.empty()) {
        return false;
    }

    return  (_pruningCornersPermutation.size() == 40320 &&
            _pruningMSlicePermutation.size() == 24 &&
            _pruningUDSlicePermutation.size() == 40320);
}

// ====================================================================================
// ==== Getter ====
// ====================================================================================


std::vector<SpinLst> G2Solver::getSolution() const {
    return _solution;
}