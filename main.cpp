#include <iostream>
#include <chrono>

#include "include/RubikController.hpp"

#include "include/BuildPruningTable/TableGenerator.hpp"
#include "include/solver/Pruning/TableIO.hpp"
#include "include/solver/Pruning/PruningTable.hpp"
#include "include/cube/Encoding.h"

#include "include/spin/SpinManager.hpp"

#include "include/engine/CubeStateHelper.hpp"
#include "include/utils/Constants.hpp"


#include "include/solver/Kociemba/KociembaSolver.hpp"

static inline int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return 1;
}




int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    if (argc != 2)
        return error("Usage: " + std::string(argv[0]) + " \" ALL SPIN \" ");

    RubikController controller;

    if (!controller.parse(argv[1]))
        return 1;
    controller.applySuffle();
    controller.print();
    controller.solve();
    controller.print();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Temps écoulé: " << elapsed.count() << " secondes\n";
    return 0;
}
