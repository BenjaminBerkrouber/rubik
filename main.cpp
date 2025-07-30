#include <iostream>
#include <chrono>

#include "include/RubikController.hpp"

#include "include/solver/Kociemba/Pruning/TableGenerator.hpp"
#include "include/solver/Kociemba/Pruning/TableIO.hpp"
#include "include/solver/Kociemba/Pruning/PruningTable.hpp"
#include "include/cube/OrientationEncoding.hpp"

#include "include/spin/SpinManager.hpp"

#include "include/engine/CubeStateHelper.hpp"
#include "include/utils/Constants.hpp"


static inline int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return 1;
}


#include <array>

bool areInverseMoves(SpinLst a, SpinLst b) {
    int faceA = static_cast<int>(a) / 3;
    int faceB = static_cast<int>(b) / 3;

    if (faceA != faceB) return false;

    int turnA = static_cast<int>(a) % 3;
    int turnB = static_cast<int>(b) % 3;
    return (turnA + turnB) == 3;
}



bool idaSolveOrientations(
    CubeState state,
    const std::vector<uint8_t>& table,
    SpinManager& spinManager,
    std::vector<SpinLst>& solution,
    int maxDepth,
    int depth = 0,
    bool hasLastMove = false,
    SpinLst lastMove = SpinLst::U // valeur arbitraire
) {
    size_t index = encodeOrientationIndex(state);
    uint8_t heuristic = table[index];

    if (heuristic == 0) {
        return true; // Résolu
    }

    if (depth + heuristic > maxDepth) {
        return false;
    }

    for (int moveInt = 0; moveInt < 18; ++moveInt) {
        SpinLst move = static_cast<SpinLst>(moveInt);

        if (hasLastMove && areInverseMoves(lastMove, move)) continue;

        CubeState next = state;
        spinManager.applyMove(next, move);
        solution.push_back(move);

        if (idaSolveOrientations(next, table, spinManager, solution, maxDepth, depth + 1, true, move)) {
            return true;
        }

        solution.pop_back();
    }

    return false;
}


bool solveOrientations(CubeState initial, const std::vector<uint8_t>& table, SpinManager& spinManager, std::vector<SpinLst>& solution) {
    for (int depth = 0; depth <= 7; ++depth) {
        solution.clear();
        if (idaSolveOrientations(initial, table, spinManager, solution, depth)) {
            return true;
        }
    }
    return false;
}



std::vector<uint8_t> getG1PruningOrientation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("g1_corners_edges.prune", table, 0x01))
        return table;

    auto newTable = TableGenerator::generate(
        encodeOrientationIndex,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        2048 * 2187
    );
    pruning::io::save("g1_corners_edges.prune", newTable, 0x01);
    return newTable;
}

std::vector<uint8_t> getG1PruningMSlice() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("g1_Mslice.prune", table, 0x02))
        return table;

    auto newTable = TableGenerator::generate(
        encodeMSlice,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        495
    );
    pruning::io::save("g1_Mslice.prune", newTable, 0x02);
    return newTable;
}




int main() {
    RubikController controller;
    SpinManager spinManager;
    
    CubeState scrambled;
    CubeStateHelper helper(scrambled);
    
    std::vector<uint8_t> table = getG1PruningOrientation();

    std::vector<SpinLst> solution;

    controller.parse("F U R D B L2 F' ");
    // controller.parse("F U R D B L2 F' D2 U' R' B' L' F2 D' U2 R2 B2 L2");

    std::vector<SpinLst> scrambleMoves = controller.getResults();
    
    std::cout << "Shuffling cube with moves: ";
    for (const auto& move : scrambleMoves) {
        spinManager.applyMove(scrambled, move);
        std::cout << spinToStr(move) << " " << std::endl;
    }
    helper.print();

    if (solveOrientations(scrambled, table, spinManager, solution)) {
        std::cout << "Orientation solved in " << solution.size() << " moves:\n";
        std::cout << "Solution: ";
        for (auto m : solution)
            std::cout << spinToStr(m) << ' ';
        std::cout << '\n';
    } else {
        std::cerr << "Failed to solve orientations within depth limit\n";
    }

    for (const auto& move : solution) {
        spinManager.applyMove(scrambled, move);
    }
    helper.print();

    return 0;
}
