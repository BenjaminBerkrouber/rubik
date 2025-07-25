

#include "./include/cube/CubeState.hpp"
#include "./include/utils/CubeStateHelper.hpp"

#include "./include/spin/Spin.hpp"
#include "./include/spin/SpinManager.hpp"

#include "./include/Cube.hpp"
#include "./include/CubePrinter.hpp"
#include <chrono>


#include <random>
#include <iostream>
#include <iomanip>

#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <array>
#include <queue>
#include <set>





#include <bitset>





void benshmark() {
    Cube cube;
    CubeState cubestate;
    SpinManager spinManager;

    int N = 40000000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        cube.applySpin(SpinId::U);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        spinManager.applyMove(cubestate, U);
    }

    end = std::chrono::high_resolution_clock::now();
    auto duration2_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    auto duration_ms = duration_ns / 1e6;
    auto duration2_ms = duration2_ns / 1e6;

    auto time_saved_ns = duration_ns - duration2_ns;
    auto time_saved_ms = duration_ms - duration2_ms;

    double percent_gain = 100.0 * time_saved_ns / duration_ns;

    std::cout << "Duration for " << N << " spins:" << std::endl;

    std::cout << "Last: " << std::endl
                << std::setw(15) << duration_ns << " ns " << std::endl
                << std::setw(15) << duration_ms << " ms" << std::endl;

    std::cout << "New:  " << std::endl
                << std::setw(15) << duration2_ns << " ns " << std::endl
                << std::setw(15) << duration2_ms << " ms" << std::endl;

    std::cout << "Gain: " << std::endl
                << std::setw(15) << time_saved_ns << " ns" << std::endl
                << std::setw(15) << time_saved_ms << " ms" << std::endl
                << std::setw(14) << std::fixed << std::setprecision(2) << percent_gain << " % faster" << std::endl;

}




void printCubeSate(const Cube& cube) {
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
}





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

std::vector<SpinLst> generateRandomSpins(int N) {
    std::vector<SpinLst> allowSPin = {
        U, U2, U3,
        D, D2, D3,
        F, F2, F3,
        B, B2, B3,
        L, L2, L3,
        R, R2, R3
    };

    std::vector<SpinLst> spins;
    spins.reserve(N);

    std::random_device rd;  // Source d'aléa
    std::mt19937 gen(rd()); // Générateur Mersenne Twister
    std::uniform_int_distribution<> distrib(0, allowSPin.size() - 1);

    for (int i = 0; i < N; ++i) {
        spins.push_back(static_cast<SpinLst>(distrib(gen)));
    }

    return spins;
}

const char* spinToStr(SpinLst spin) {
    switch (spin) {
        case U: return "U"; case U2: return "U2"; case U3: return "U3";
        case D: return "D"; case D2: return "D2"; case D3: return "D3";
        case F: return "F"; case F2: return "F2"; case F3: return "F3";
        case B: return "B"; case B2: return "B2"; case B3: return "B3";
        case L: return "L"; case L2: return "L2"; case L3: return "L3";
        case R: return "R"; case R2: return "R2"; case R3: return "R3";
        default: return "UNKNOWN";
    }
}


SpinLst invertSpin(SpinLst spin) {
    switch (spin) {
        case U:  return U3;
        case U2: return U2;
        case U3: return U;
        case D:  return D3;
        case D2: return D2;
        case D3: return D;
        case F:  return F3;
        case F2: return F2;
        case F3: return F;
        case B:  return B3;
        case B2: return B2;
        case B3: return B;
        case L:  return L3;
        case L2: return L2;
        case L3: return L;
        case R:  return R3;
        case R2: return R2;
        case R3: return R;
        default: return spin;
    }
}


std::vector<SpinLst> invertSpinSequence(const std::vector<SpinLst>& sequence) {
    std::vector<SpinLst> inverted;
    inverted.reserve(sequence.size());

    for (auto it = sequence.rbegin(); it != sequence.rend(); ++it) {
        inverted.push_back(invertSpin(*it));
    }

    return inverted;
}

void sexyMove(CubeState &state) {
    CubeStateHelper helper(state);
    SpinManager spinManager;
    std::cout << "Performing sexy move sequence:" << std::endl;
    spinManager.applyMove(state, SpinLst::R);
    std::cout << "After R:" << std::endl;
    helper.printState();
    helper.printCube();
    spinManager.applyMove(state, SpinLst::U);
    std::cout << "After U:" << std::endl;
    helper.printState();
    helper.printCube();
    spinManager.applyMove(state, SpinLst::R3);
    std::cout << "After R3:" << std::endl;
    helper.printState();
    helper.printCube();
    spinManager.applyMove(state, SpinLst::U3);
    std::cout << "After U3:" << std::endl;
    helper.printState();
    helper.printCube();
}

int main() {

    benshmark();

    // CubeState cubestate;
    // SpinManager spinManager;
    // CubeStateHelper helper(cubestate);
    
    // // Cube cube;
    // // cube.applySpin(SpinId::D);
    // // CubePrinter printer(cube);
    // // printCubeSate(cube);
    // // printer.print();
    // helper.printState();
    // helper.printCube();


    // std::vector<SpinLst> randomSpins = generateRandomSpins(50000000);
    // std::vector<SpinLst> invertedSpins = invertSpinSequence(randomSpins);
    // (void)randomSpins; // To avoid unused variable warning
    // (void)invertedSpins; // To avoid unused variable warning

    // // std::vector<SpinLst> spintest = {
    // //     F3,
    // //     B2,
    // //     L,
    // // };

    // // std::vector<SpinLst> invertedSpintest = invertSpinSequence(spintest);

    // std::cout << "----------------------------------------" << std::endl;
    // std::cout << "Applying random moves: " << std::endl;
    // for (const auto& spin : randomSpins) {
    //     // std::cout << spinToStr(spin) << " ";
    //     spinManager.applyMove(cubestate, spin);
    //     // helper.printCube();
    // }
    // std::cout << std::endl;
    // helper.printCube();
    // std::cout << std::endl;
    // std::cout << "----------------------------------------" << std::endl;
    // std::cout << "Applying inverted moves: " << std::endl;
    // for (const auto& spin : invertedSpins) {
    //     // std::cout << spinToStr(spin) << " ";
    //     spinManager.applyMove(cubestate, spin);
    //     // helper.printCube();
    // }
    // std::cout << std::endl;

    // helper.printCube();


    // printSpin(cubestate, SpinLst::B);
    // printSpin(cubestate, SpinLst::F);
    // printSpin(cubestate, SpinLst::U2);

    // printSpin(cubestate, SpinLst::B3);
    // printSpin(cubestate, SpinLst::B);
    // printSpin(cubestate, SpinLst::F3);
    // printSpin(cubestate, SpinLst::U3);
    // printSpin(cubestate, SpinLst::F);
    // printSpin(cubestate, SpinLst::F);
    // printSpin(cubestate, SpinLst::U3);
    // printSpin(cubestate, SpinLst::U);
    // printSpin(cubestate, SpinLst::F);
    

    // for (int i = 0; i < 6; ++i) {
    //     sexyMove(cubestate);
    // }




    return 0;
}