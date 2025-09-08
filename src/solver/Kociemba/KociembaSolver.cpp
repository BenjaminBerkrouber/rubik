#include "../../../include/solver/Kociemba/KociembaSolver.hpp"
#include "../../../include/cube/Encoding.h"

// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


KociembaSolver::KociembaSolver(CubeState &state) : _state(state) {
    _g1Solver = G1Solver();
    _g2Solver = G2Solver();
}

KociembaSolver::~KociembaSolver() = default;


// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================


static bool error(const char* msg) {
    std::cerr << msg << std::endl;
    return false;
}

bool KociembaSolver::solve() {
    if (!checkTable())
        return error("[KO] Pruning tables are not loaded correctly");
    
    if (!_g1Solver.solve(_state))
        return error("[KO] G1Solver failed to solve the cube.");
    for (const SpinLst& move : _g1Solver.getSolution())
        _spinManager.applyMove(_state, move);

    if (!_g2Solver.solve(_state))
        return error("[KO] G2Solver failed to solve the cube.");
    for (const SpinLst& move : _g2Solver.getSolution())
        _spinManager.applyMove(_state, move);
    
    return true;
}

// =====================================================================================
// ==== Utils methode ====
// =====================================================================================


bool KociembaSolver::checkTable() const {
    return _g1Solver.checkTable() && _g2Solver.checkTable();
}


// ====================================================================================
// ==== Getter ====
// ====================================================================================


std::vector<SpinLst> KociembaSolver::getSolution() const {
    std::vector<SpinLst> g1Solution = _g1Solver.getSolution();
    std::vector<SpinLst> g2Solution = _g2Solver.getSolution();
    g1Solution.insert(g1Solution.end(), g2Solution.begin(), g2Solution.end());
    return g1Solution;
}


std::vector<std::pair<std::string, std::pair<std::vector<SpinLst>, std::vector<SpinLst>>>> KociembaSolver::getSolutionSteps() const {
    std::vector<std::pair<std::string, std::pair<std::vector<SpinLst>, std::vector<SpinLst>>>> steps;
    steps.push_back(
        std::make_pair(
            "G1\n\nGoal: Move the cube into a special subgroup denoted by G1.\n- In this subgroup, certain constraints are already met:\n    1. Edge orientation -> all edges are oriented correctly.\n    2. Corner orientation -> all corners are oriented correctly.\n    3. Middle slice edges (M-slice) -> they must be in the 'right layer' (in the middle, not necessarily in the right place).\n\nPhase 1 does not seek to solve the cube but to transform it into a simpler state where it will be easy to complete.",
            std::make_pair(
                _g1Solver.getSolution(),
                getInverseSpins(_g1Solver.getSolution())
            )
        )
    );
    steps.push_back(
        std::make_pair(
            "G2\n\nGoal: Move from the state achieved in Phase 1 to the solved state.\nHere, the constraints of Phase 1 allow us to limit ourselves to a smaller subgroup of moves (U, D, R2, L2, F2, B2) -> therefore only half-turns to the side plus up/down rotations.\n\nIn this phase:\n    1. The middle edges are replaced correctly.\n    2. The corners and edges are positioned correctly.\n    3. The entire cube is solved.\n",
            std::make_pair(
                _g2Solver.getSolution(),
                getInverseSpins(_g2Solver.getSolution())
            )
        )
    );
    return steps;
}