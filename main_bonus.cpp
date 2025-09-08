#include <iostream>

#include "_bonus/RubikController_bonus.hpp"
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
