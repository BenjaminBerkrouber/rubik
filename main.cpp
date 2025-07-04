#include "./include/Cube.hpp"
#include "./include/CubePrinter.hpp"
#include <chrono>

#include "./include/algo/Kociemba/Pruning/PruningTableG1.hpp"


#include <random>
#include <iostream>


#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <array>
#include <queue>
#include <set>


constexpr int MAX_DEPTH = 12; // raisonnable pour QTM


std::vector<SpinId> spins = {
    SpinId::U,
    SpinId::D,
    SpinId::L,
    SpinId::R,
    SpinId::F,
    SpinId::B,
    SpinId::U2,
    SpinId::D2,
    SpinId::L2,
    SpinId::R2,
    SpinId::F2,
    SpinId::B2,
    SpinId::U_PRIME,
    SpinId::D_PRIME,
    SpinId::L_PRIME,
    SpinId::R_PRIME,
    SpinId::F_PRIME,
    SpinId::B_PRIME
};

bool searchPhase1(Cube& cube, int depth, int maxDepth, std::vector<SpinId>& path, PruningTableG1& pruning) {
    if (depth == maxDepth) {
        if (pruning.encodeCornersOrientation(cube.getCornerOrientations()) == 0
            && pruning.encodeEgdeOrientation(cube.getEdgeOrientations()) == 0
            && pruning.encodeEdgesSlice(cube.getEdges()) == 0
        ) {
            return true;
        }
        return false;
    }


    for (SpinId move : spins) {
        Cube next = cube;
        next.applySpin(move);

        int cornerIdx = pruning.encodeCornersOrientation(next.getCornerOrientations());
        int edgeIdx = pruning.encodeEgdeOrientation(next.getEdgeOrientations());
        int sliceIdx = pruning.encodeEdgesSlice(next.getEdges());

        int heuristic = std::max({
            pruning.getCornersOrientationPruningTable()[cornerIdx],
            pruning.getEdgesOrientationPruningTable()[edgeIdx],
            pruning.getEdgesSlicePruningTable()[sliceIdx]
        });

        if (depth + heuristic <= maxDepth) {
            path.push_back(move);
            if (searchPhase1(next, depth + 1, maxDepth, path, pruning))
                return true;
            path.pop_back();
        }
    }

    return false;
}






















void randomShuffle(Cube& cube, int moves = 20) {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, spins.size() - 1);

    for (int i = 0; i < moves; ++i) {
        cube.applySpin(spins[dis(gen)]);
    }
}



void printCubeState(const Cube& cube, CubePrinter& printer) {
    std::cout << "================= Cube state =================" << std::endl << std::endl;
    std::cout << "Corners:             ";
    for (const auto& corner : cube.getCorners()) {
        std::cout << static_cast<int>(corner) << " ";
    }
    std::cout << std::endl << "Corners Orientation: ";
    for (const auto& cornerOrientation : cube.getCornerOrientations()) {
        std::cout << static_cast<int>(cornerOrientation) << " ";
    }
    std::cout << std::endl << "Edge:                ";
    for (const auto& edge : cube.getEdges()) {
        std::cout << static_cast<int>(edge) << " ";
    }
    std::cout << std::endl << "Edge Orientation:    ";
    for (const auto& edgeOrientation : cube.getEdgeOrientations()) {
        std::cout << static_cast<int>(edgeOrientation) << " ";
    }
    std::cout << std::endl;
    printer.print();
    std::cout << std::endl;
}

void printMaxDeath(const Cube &cube, const PruningTableG1 &pruningTableG1) {
    int cornerIndex = pruningTableG1.encodeCornersOrientation(cube.getCornerOrientations());
    int edgeIndex = pruningTableG1.encodeEgdeOrientation(cube.getEdgeOrientations());
    int sliceIndex = pruningTableG1.encodeEdgesSlice(cube.getEdges());

    std::cout << "Corner table depth: " << unsigned(pruningTableG1.getCornersOrientationPruningTable()[cornerIndex]) << '\n';
    std::cout << "Edge table depth: " << unsigned(pruningTableG1.getEdgesOrientationPruningTable()[edgeIndex]) << '\n';
    std::cout << "Slice table depth: " << unsigned(pruningTableG1.getEdgesSlicePruningTable()[sliceIndex]) << '\n';
}

std::vector<SpinId> searchSolvePhase1(Cube& cube, PruningTableG1& pruningTableG1) {
    std::cout << "Starting Phase 1 search..." << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<SpinId> solution;
    for (int depth = 0; depth < MAX_DEPTH; ++depth) {
        if (searchPhase1(cube, 0, depth, solution, pruningTableG1)) {
            std::cout << "Phase 1 solution found in " << solution.size() << " moves." << std::endl;
            break;
        } else {
            std::cout << "No solution found at depth " << depth << ". Trying deeper..." << std::endl;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    std::cout << "["<< elapsed.count() << "] s.  " << "[" << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << "] ms" << std::endl;
    return solution;
} 

void applySolve(Cube& cube, const std::vector<SpinId>& solution) {
    for (const auto& move : solution) {
        cube.applySpin(move);
    }
}



int main() {

    std::cout << sizeof(std::array<uint8_t, 8>) << " bytes for corners" << std::endl;
    std::cout << sizeof(uint32_t) << " bytes for corners" << std::endl;

    Cube cube;
    CubePrinter printer(cube);
    PruningTableG1 pruningTableG1;


    printCubeState(cube, printer);

    std::cout << "encoding slice: " << pruningTableG1.encodeEdgesSlice(cube.getEdges()) << std::endl;

    // cube.applySpin(SpinId::U);


    // printCubeState(cube, printer);
    // std::cout << "cornerEncoding: " << pruningTableG1.encodeCornersOrientation(cube.getCornerOrientations()) << std::endl;

    // randomShuffle(cube, 20);
    // printCubeState(cube, printer);

    // printMaxDeath(cube, pruningTableG1);


    // std::vector<SpinId> solveSpins = searchSolvePhase1(cube, pruningTableG1);
    // applySolve(cube, solveSpins);

    // printCubeState(cube, printer);

    return 0;
}