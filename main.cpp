#include "./include/Cube.hpp"
#include "./include/CubePrinter.hpp"
#include <chrono>

#include <iostream>

void applySpin(Cube& cube, CubePrinter printer, SpinId id, bool verbose = true) {
    cube.applySpin(id);
    if (verbose) {
        std::cout << std::endl;
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
        std::cout << std::endl << std::endl;
        printer.print();
    }
}

#include "Renderer.hpp"

int main() {

    // Cube cube;
    // CubePrinter printer(cube);

    // printer.print();
    // applySpin(cube, printer,  SpinId::U);
    // applySpin(cube, printer,  SpinId::U);

    Renderer renderer{};

    if (!renderer.init()) {

        std::cerr << "Failed to initialize renderer." << std::endl;
        return (-1);
    }

    renderer.renderLoop();

    return (0);
}
