
#include "./include/cube/CubeState.hpp"
#include "./include/engine/CubeStateHelper.hpp"

#include "./include/spin/Spin.hpp"
#include "./include/spin/SpinManager.hpp"


#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <array>
#include <queue>
#include <set>
#include <random>
#include <iostream>
#include <iomanip>

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

    std::random_device rd;
    std::mt19937 gen(rd());
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


void checkSuffleReverse() {
    CubeState cubestate;
    SpinManager spinManager;

    std::vector<SpinLst> randomSpins = generateRandomSpins(50000000);
    std::vector<SpinLst> invertedSpins = invertSpinSequence(randomSpins);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Applying random moves: " << std::endl;
    for (const auto& spin : randomSpins) {
        spinManager.applyMove(cubestate, spin);
        CubeStateHelper helper(cubestate);
        helper.printState();
        helper.print();
        std::cout << "----------------------------------------" << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Applying inverted moves: " << std::endl;
    for (const auto& spin : invertedSpins) {
        spinManager.applyMove(cubestate, spin);
        CubeStateHelper helper(cubestate);
        helper.printState();
        helper.print();
        std::cout << "----------------------------------------" << std::endl;
    }
}