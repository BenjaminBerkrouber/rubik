#include <iostream>
#include <chrono>

#include "include/RubikController.hpp"

#include "include/BuildPruningTable/TableGenerator.hpp"
#include "include/solver/Pruning/TableIO.hpp"
#include "include/cube/Encoding.h"

#include "include/spin/SpinManager.hpp"

#include "include/engine/CubeStateHelper.hpp"
#include "include/utils/Constants.hpp"


#include "include/solver/Kociemba/KociembaSolver.hpp"

static inline int error(const std::string& message) {
    std::cerr << "[KO] | " << message << std::endl;
    return 1;
}

#include "renderer/Renderer.hpp"

int main() {

// int main(int argc, char* argv[]) {
//     if (argc != 2)    
//         return error("Usage: " + std::string(argv[0]) + " \" ALL SPIN \" ");

//     RubikController controller;

//     ParseResult result = controller.parse(argv[1]);
//     if (!result.ok) return error("Parsing error: " + result.message);
//     controller.applySuffle();
//     // controller.print();
//     controller.solve();
//     // controller.print();
//     return 0;

    Renderer renderer{};

    if (!renderer.init()) {

        std::cerr << "Failed to initialize renderer." << std::endl;
        return (-1);
    }

    renderer.renderLoop();

    return (0);
}
