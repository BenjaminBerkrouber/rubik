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
    steps.push_back(std::make_pair("G1", std::make_pair(_g1Solver.getSolution(), getInverseSpins(_g1Solver.getSolution()))));
    steps.push_back(std::make_pair("G2", std::make_pair(_g2Solver.getSolution(), getInverseSpins(_g2Solver.getSolution()))));
    return steps;
}