#include "./include/Cube.hpp"

#include <iostream>

void applySpin(Cube& cube, SpinId id, bool verbose = true) {
    cube.applySpin(id);
    if (verbose) {
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

    applySpin(cube, SpinId::D2);



    return 0;
}