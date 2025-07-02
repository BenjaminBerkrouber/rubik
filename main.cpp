#include "./include/Cube.hpp"

#include <iostream>

void applySpin(Cube& cube, const std::string& spin, bool verbose = true) {
    cube.applySpin(spin);
    if (verbose) {
        std::cout << "Applied spin: " << spin << std::endl;
        std::cout << "Corners: " << cube.getCorners() << std::endl;
        std::cout << "Corners orientations: " << cube.getCornerOrientations() << std::endl;
        std::cout << "Edges: " << cube.getEdges() << std::endl;
        std::cout << "Edges orientations: " << cube.getEdgeOrientations() << std::endl;
        std::cout << "Cube state after spin:" << std::endl;
        cube.print();
    }
}


int main() {
    Cube cube;

    cube.print();

    std::vector<std::string> sexyMove = {
        "R", "U", "R'", "U'"
    };

    for ( int i = 0; i < 6; ++i) {
        for (const auto& spin : sexyMove) {
            applySpin(cube, spin);
        }
    }



    return 0;
}