#include <iostream>
#include <chrono>

#include "include/_bonus/RubikController_bonus.hpp"

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

    Renderer renderer;
    RubikController controller(&renderer);

    if (!renderer.init(&controller)) {

        std::cerr << "Failed to initialize renderer." << std::endl;
        return (-1);
    }

    renderer.renderLoop();

    return (0);
}

