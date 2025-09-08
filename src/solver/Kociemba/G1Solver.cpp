#include "../../../include/solver/Kociemba/G1Solver.hpp"


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================

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



G1Solver::G1Solver() : _spinManager() {
    pruning::io::load("./table/Kociemba/g1_corners_edges.prune", _pruningOrientation, 0x01);
    pruning::io::load("./table/Kociemba/g1_Mslice.prune", _pruningMSlice, 0x02);


    try {
        p1Tables_ = MoveTables::load("p1_moves.bin");
    } catch (...) {
        p1Tables_ = MoveTables::buildOnline(
            _spinManager,
            [this](CubeState& s, uint16_t t){ decodeCornersOrientation(s, t); },
            [this](CubeState& s, uint16_t f){ decodeEdgesOrientation(s, f); },
            [this](CubeState& s, uint16_t m){
                auto pos = unrankMSlice(m);
                uint8_t nextNonSlice = 0;
                std::array<bool,12> isSlice{}; for (auto p : pos) isSlice[p] = true;
                for (int p = 0; p < 12; ++p) {
                    if (!isSlice[p]) setEdgeId(s, p, nextNonSlice++);
                }
                for (int i = 0; i < 4; ++i) setEdgeId(s, pos[i], 8 + i);
            },
            [this](const CubeState& s){ return encodeCornersOrientation(s); },
            [this](const CubeState& s){ return encodeEdgesOrientation(s); },
            [this](const CubeState& s){ return encodeMSlice(s); }
        );
        p1Tables_.save("p1_moves.bin");
    }
}


// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================

inline bool axisOf(SpinLst m) {
    return static_cast<int>(m) / 3;
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
        if (hasLastMove && axisOf(lastMove) == axisOf(move)) continue;
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



bool G1Solver::solve(CubeState& state) {
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
    return (_pruningOrientation.size() == 2048 * 2187 && 
            _pruningMSlice.size() == 495);
}

// ====================================================================================
// ==== Getter ====
// ====================================================================================


std::vector<SpinLst> G1Solver::getSolution() const {
    return _solution;
}