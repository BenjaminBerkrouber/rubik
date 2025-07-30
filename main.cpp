#include <iostream>
#include <chrono>

#include "include/RubikController.hpp"


static inline int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return 1;
}


int main(int argc, char* argv[]) {

    if (argc != 2)
        return error("Usage: " + std::string(argv[0]) + " \" ALL SPIN \" ");

    RubikController controller;

    if (!controller.parse(argv[1]))
        return 1;
    controller.applySuffle();
    controller.print();
    controller.solve();
    // controller.print();


    return 0;
}