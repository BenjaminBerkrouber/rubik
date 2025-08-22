#include "../../../include/solver/Thistlethwaite/IPhaseSolver.hpp"
#include "../../../include/engine/CubeStateHelper.hpp"

bool IPhaseSolver::IDA(
    CubeState state,
    int maxDepth,
    int depth = 0,
    bool hasLastMove = false,
    SpinLst lastMove = SpinLst::U
) {

    uint8_t heuristic = _pruning[encodage(state)];
    if (heuristic == 0) return true;
    if (depth + heuristic > maxDepth) return false;

    for (const SpinLst& move : _allowSpins) {
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


bool IPhaseSolver::areInverseMoves(SpinLst a, SpinLst b) {
    int faceA = static_cast<int>(a) / 3;
    int faceB = static_cast<int>(b) / 3;

    if (faceA != faceB) return false;

    int turnA = static_cast<int>(a) % 3;
    int turnB = static_cast<int>(b) % 3;
    return (turnA + turnB) == 3;
}

bool IPhaseSolver::checkTable() const {
    return (_pruning.size() == _pruningSize);
}

bool IPhaseSolver::solve(CubeState &state) {
    for (int depth = 0; depth <= _maxDepth; ++depth) {
        _solution.clear();
        // std::cout << "Trying depth: " << depth << std::endl;
        if (IDA(state, depth)) return true;
    }
    return false;
}

std::vector<SpinLst> IPhaseSolver::getSolution() const {
    return _solution;
}
