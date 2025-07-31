#include "../../../include/solver/Kociemba/KociembaSolver.hpp"
#include "../../../include/engine/CubeStateHelper.hpp"
#include <iostream>

int getCornerParity(const CubeState& state) {
    uint8_t cornerPos[8];
    for (int i = 0; i < 8; ++i) {
        cornerPos[i] = (state.corners >> (i * 4)) & 0xF;
    }

    int parity = 0;
    bool visited[8] = {false};

    for (int i = 0; i < 8; ++i) {
        if (visited[i])
            continue;

        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = cornerPos[j];
            ++cycle_size;
        }

        if (cycle_size > 1)
            parity += cycle_size - 1;
    }

    return parity % 2; // 0 = pair, 1 = impair
}

int getUDEdgeParity(const CubeState& state) {
    uint8_t edgePos[8];
    for (int i = 0; i < 8; ++i) {
        edgePos[i] = (state.edges >> (i * 4)) & 0xF;
    }

    int parity = 0;
    bool visited[8] = {false};

    for (int i = 0; i < 8; ++i) {
        if (visited[i])
            continue;

        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            j = edgePos[j];
            ++cycle_size;
        }

        if (cycle_size > 1)
            parity += cycle_size - 1;
    }

    return parity % 2; // 0 = pair, 1 = impair
}

bool isValidG2Parity(const CubeState& state) {
    return getCornerParity(state) == getUDEdgeParity(state);
}

KociembaSolver::KociembaSolver(CubeState &state) : _state(state) {
    _g1Solver = G1Solver();
    _g2Solver = G2Solver();
}

KociembaSolver::~KociembaSolver() = default;


bool KociembaSolver::solve() {
    CubeStateHelper helper(_state);
    SpinManager spinManager;
    std::cout << "================================== Kociemba's Algorithm ==================================" << std::endl;
    
    std::cout << "===== Step 1: G1 Solver =====" << std::endl;
        if (!_g1Solver.solve(_state)) {
            std::cerr << "Failed to solve the cube with G1 solver." << std::endl;
            return false;
        }
            for (const SpinLst& move : _g1Solver.getSolution()) {
                spinManager.applyMove(_state, move);
            }
            helper.print();
    
    std::cout << "===== Step 2: G2 Solver =====" << std::endl;
        // if (!_g2Solver.solve(_state)) {
        //     std::cerr << "Failed to solve the cube with G2 solver." << std::endl;
        //     return false;
        // }
        //     for (const SpinLst& move : _g2Solver.getSolution()) {
        //         spinManager.applyMove(_state, move);
        //     }
        //     helper.print();
    

    // if (!isValidG2Parity(_state)) {
    //     std::cout << "Invalid G2 parity detected in the cube state." << std::endl;
    // } else {
    //     std::cout << "G2 parity is valid." << std::endl << std::endl;
    // }

    return true;
}


std::vector<SpinLst> KociembaSolver::getSolution() const {
    std::vector<SpinLst> g1Solution = _g1Solver.getSolution();
    std::vector<SpinLst> g2Solution = _g2Solver.getSolution();
    g1Solution.insert(g1Solution.end(), g2Solution.begin(), g2Solution.end());
    return g1Solution;
}
