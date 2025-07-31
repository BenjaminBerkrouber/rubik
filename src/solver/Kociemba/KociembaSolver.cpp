#include "../../../include/solver/Kociemba/KociembaSolver.hpp"
#include "../../../include/engine/CubeStateHelper.hpp"
#include <iostream>

KociembaSolver::KociembaSolver(CubeState &state) : _state(state) {
    _g1Solver = G1Solver();
    _g2Solver = G2Solver();
}

KociembaSolver::~KociembaSolver() = default;


bool KociembaSolver::solve() {
    CubeStateHelper helper(_state);
    SpinManager spinManager;
    // std::cout << "================================== Kociemba's Algorithm ==================================" << std::endl;
    
    // std::cout << "===== Step 1: G1 Solver =====" << std::endl;
        if (!_g1Solver.solve(_state)) {
            // std::cerr << "Failed to solve the cube with G1 solver." << std::endl;
            return false;
        }
        std::vector<SpinLst> g1Solution = _g1Solver.getSolution();
        // std::cout << "G1 Solution: " << g1Solution.size() << " moves" << std::endl;
            for (const SpinLst& move : g1Solution) {
                spinManager.applyMove(_state, move);
            }
            // helper.print();
    
    // std::cout << "===== Step 2: G2 Solver =====" << std::endl;
        if (!_g2Solver.solve(_state)) {
            // std::cerr << "Failed to solve the cube with G2 solver." << std::endl;
            return false;
        }
        std::vector<SpinLst> g2Solution = _g2Solver.getSolution();
        // std::cout << "G2 Solution: " << g2Solution.size() << " moves" << std::endl;
            for (const SpinLst& move : g2Solution) {
                spinManager.applyMove(_state, move);
            }
            // helper.print();
    return true;
}


std::vector<SpinLst> KociembaSolver::getSolution() const {
    std::vector<SpinLst> g1Solution = _g1Solver.getSolution();
    std::vector<SpinLst> g2Solution = _g2Solver.getSolution();
    g1Solution.insert(g1Solution.end(), g2Solution.begin(), g2Solution.end());
    return g1Solution;
}
