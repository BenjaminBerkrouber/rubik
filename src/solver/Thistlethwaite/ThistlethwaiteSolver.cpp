#include "../../../include/solver/Thistlethwaite/ThistlethwaiteSolver.hpp"
#include "../../../include/engine/CubeStateHelper.hpp"
#include "../../../include/utils/utils.h"

// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


ThistlethwaiteSolver::ThistlethwaiteSolver(CubeState &state) : _state(state) {
    _phaseSolvers.push_back(new Phase1Solver());
    _phaseSolvers.push_back(new Phase2Solver());
    _phaseSolvers.push_back(new Phase3Solver());
    _phaseSolvers.push_back(new Phase4Solver());
}

ThistlethwaiteSolver::~ThistlethwaiteSolver() {
    for (IPhaseSolver* phaseSolver : _phaseSolvers) {
        delete phaseSolver;
    }
    _phaseSolvers.clear();
};


// ==============================================================================================================================
// ==== Solve Method ====
// ==============================================================================================================================


bool ThistlethwaiteSolver::solve() {
    CubeStateHelper helper(_state);
    
    if (!checkTable()) {
        std::cerr << "[KO] Pruning tables are not loaded correctly." << std::endl;
        return false;
    }

    int i = 0;

    for (IPhaseSolver* phaseSolver : _phaseSolvers) {
        if (!phaseSolver->solve(_state)) {
            return false;
        }
        std::vector<SpinLst> solution = phaseSolver->getSolution();
        for (const SpinLst& move : solution) {
            _spinManager.applyMove(_state, move);
            std::cout << spinToStr(move) << " ";
        }
        std::cout << std::endl;
    }

    return true;
}



// =====================================================================================
// ==== Utils methode ====
// =====================================================================================


bool ThistlethwaiteSolver::checkTable() const {
    for (const IPhaseSolver* phaseSolver : _phaseSolvers) {
        if (!phaseSolver->checkTable()) {
            std::cerr << "[KO] Phase solver table check failed." << std::endl;
            return false;
        }
    }
    return true;
}


// ====================================================================================
// ==== Getter ====
// ====================================================================================


std::vector<SpinLst> ThistlethwaiteSolver::getSolution() const {
    std::vector<SpinLst> solution;
    for (const IPhaseSolver* phaseSolver : _phaseSolvers) {
        const auto& phaseSolution = phaseSolver->getSolution();
        solution.insert(solution.end(), phaseSolution.begin(), phaseSolution.end());
    }
    return solution;
}
