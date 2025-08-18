#include "../../../include/solver/Kociemba/KociembaSolver.hpp"

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


bool KociembaSolver::solve() {
    if (!checkTable()) {
        std::cerr << "[KO] Pruning tables are not loaded correctly." << std::endl;
        return false;
    }
    if (!_g1Solver.solve(_state)) {
        std::cerr << "[KO] G1Solver failed to solve the cube." << std::endl;
        return false;
    }
    for (const SpinLst& move : _g1Solver.getSolution()) {
        _spinManager.applyMove(_state, move);
    }

    if (!_g2Solver.solve(_state)) {
        std::cerr << "[KO] G2Solver failed to solve the cube." << std::endl;
        return false;
    }
    for (const SpinLst& move : _g2Solver.getSolution()) {
        _spinManager.applyMove(_state, move);
    }
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