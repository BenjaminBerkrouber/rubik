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



bool idaSolveG1(
    CubeState state,
    const std::vector<uint8_t>& tableOrientation,
    const std::vector<uint8_t>& tableMSlice,
    SpinManager& spinManager,
    std::vector<SpinLst>& solution,
    int maxDepth,
    int depth = 0,
    bool hasLastMove = false,
    SpinLst lastMove = SpinLst::U
) {
    size_t indexOrient = encodeOrientationIndex(state);
    size_t indexMSlice = encodeMSlice(state);

    uint8_t h1 = tableOrientation[indexOrient];
    uint8_t h2 = tableMSlice[indexMSlice];
    uint8_t heuristic = std::max(h1, h2);

    if (heuristic == 0) return true;
    if (depth + heuristic > maxDepth) return false;

    for (int moveInt = 0; moveInt < 18; ++moveInt) {
        SpinLst move = static_cast<SpinLst>(moveInt);
        if (hasLastMove && areInverseMoves(lastMove, move)) continue;

        CubeState next = state;
        spinManager.applyMove(next, move);
        solution.push_back(move);

        if (idaSolveG1(next, tableOrientation, tableMSlice, spinManager, solution, maxDepth, depth + 1, true, move)) {
            return true;
        }

        solution.pop_back();
    }

    return false;
}



bool solveG1(
    CubeState initial,
    const std::vector<uint8_t>& tableOrientation,
    const std::vector<uint8_t>& tableMSlice,
    SpinManager& spinManager,
    std::vector<SpinLst>& solution
) {
    for (int depth = 0; depth <= 10; ++depth) {
        solution.clear();
        if (idaSolveG1(initial, tableOrientation, tableMSlice, spinManager, solution, depth)) {
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
    

    std::vector<uint8_t> pruningOrientationTable = getG1PruningOrientation();
    std::vector<uint8_t> pruningMSlice = getG1PruningMSlice();

    std::vector<SpinLst> solution;

    // controller.parse("F U R D B L2 F' ");
    controller.parse("F U R D B L2 F' D2 U' R' B' L' F2 D' U2 R2 B2 L2");

    std::vector<SpinLst> scrambleMoves = controller.getResults();
    
    std::cout << "Shuffling cube with moves: ";
    for (const auto& move : scrambleMoves) {
        spinManager.applyMove(scrambled, move);
        // std::cout << spinToStr(move) << " " << std::endl;
    }
    helper.print();

    if (solveG1(scrambled, pruningOrientationTable, pruningMSlice, spinManager, solution)) {
        std::cout << "G1 résolu en " << solution.size() << " moves :\n";
        // for (auto m : solution)
        //     std::cout << spinToStr(m) << ' ';
        std::cout << '\n';
    } else {
        std::cerr << "Échec résolution G1\n";
    }

    for (const auto& move : solution) {
        spinManager.applyMove(scrambled, move);
    }
    helper.print();

    return 0;
}
