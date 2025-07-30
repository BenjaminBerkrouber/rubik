#include "./include/cube/CubeState.hpp"
#include "./include/utils/CubeStateHelper.hpp"

#include "./include/spin/Spin.hpp"
#include "./include/spin/SpinManager.hpp"

#include "./include/utils/utils.h"
#include "./include/parser/Parser.hpp"

#include <iostream>
#include <iomanip>

#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <array>
#include <queue>
#include <set>







void printSpin(CubeState& cubestate, SpinLst spin) {
    SpinManager spinManager;
    std::cout << std::endl;
    std::cout << "Applying move: " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    spinManager.applyMove(cubestate, spin);
    CubeStateHelper helper(cubestate);
    helper.printState();
    helper.printCube();
    std::cout << "----------------------------------------" << std::endl;
}

int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return 1;
}

#include <chrono>

int main(int argc, char* argv[]) {
    Parser parser;

    std::string input = "U D F B L R";
    if (argc != 2) return error("Usage: " + std::string(argv[0]) + " \" ALL SPIN \" ");
    
    ParseResult parsed = parser.parse(argv[1]);
    if (!parsed.ok) return error(std::string(parsed.message));

    std::vector<SpinLst> results = parser.getResults();
    std::cout << "Parsed moves: ";
    for (const auto& move : results) {
        std::cout << spinToStr(move) << " ";
    }
    std::cout << std::endl;

    // CubeState cubestate;
    // SpinManager spinManager;
    // CubeStateHelper helper(cubestate);
    
    // helper.printState();
    // helper.printCube();


    // printSpin(cubestate, SpinLst::B);

    // helper.printState();
    // helper.printCube();

    // checkSuffleReverse();

    return 0;
}