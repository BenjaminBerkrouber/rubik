#include "./include/cube/CubeState.hpp"
#include "./include/utils/CubeStateHelper.hpp"

#include "./include/spin/Spin.hpp"
#include "./include/spin/SpinManager.hpp"

#include "./include/utils.h"

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



int main() {

    CubeState cubestate;
    SpinManager spinManager;
    CubeStateHelper helper(cubestate);
    
    helper.printState();
    helper.printCube();


    printSpin(cubestate, SpinLst::B);

    helper.printState();
    helper.printCube();

    // checkSuffleReverse();

    return 0;
}