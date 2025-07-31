
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


#include <iostream>
#include <chrono>

#include "include/RubikController.hpp"

#include "include/BuildPruningTable/TableGenerator.hpp"
#include "include/solver/Pruning/TableIO.hpp"
#include "include/solver/Pruning/PruningTable.hpp"
#include "include/cube/Encoding.h"

#include "include/spin/SpinManager.hpp"

#include "include/engine/CubeStateHelper.hpp"
#include "include/utils/Constants.hpp"

#include "include/solver/Kociemba/KociembaSolver.hpp"

// static inline int error(const std::string& message) {
//     std::cerr << "Error: " << message << std::endl;
//     return 1;
// }




// int main(int argc, char* argv[]) {
//     auto start = std::chrono::high_resolution_clock::now();

//     if (argc != 2)
//         return error("Usage: " + std::string(argv[0]) + " \" ALL SPIN \" ");

//     RubikController controller;

//     if (!controller.parse(argv[1]))
//         return 1;
//     controller.applySuffle();
//     controller.print();
//     controller.solve();
//     controller.print();

//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> elapsed = end - start;
//     std::cout << "Temps écoulé: " << elapsed.count() << " secondes\n";
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <array>
#include <cassert>


bool compareCornerPermutation(const CubeState& a, const CubeState& b) {
    for (int i = 0; i < 8; ++i) {
        uint8_t pa = (a.corners >> (i * 4)) & 0xF;
        uint8_t pb = (b.corners >> (i * 4)) & 0xF;
        if (pa != pb)
            return false;
    }
    return true;
}

#include <unordered_set>
#include <algorithm>

void testAllCornerPermutations() {
    std::array<uint8_t, 8> perm = {0, 1, 2, 3, 4, 5, 6, 7};
    std::unordered_set<uint32_t> seenIndexes;

    size_t count = 0;
    do {
        CubeState original{};
        original.corners = 0;

        for (int i = 0; i < 8; ++i) {
            original.corners |= (uint64_t(perm[i]) & 0xF) << (i * 4);
        }

        uint32_t index = encodeCornerPermutation(original);

        // Vérifie qu’on n’a pas encore vu cet index
        if (!seenIndexes.insert(index).second) {
            std::cerr << "❌ Collision détectée à l’index " << index << " pour la permutation :\n";
            for (int i = 0; i < 8; ++i) {
                std::cerr << "  perm[" << i << "] = " << +perm[i] << "\n";
            }
            assert(false);
        }

        CubeState decoded{};
        decodeCornerPermutation(decoded, index);

        if (!compareCornerPermutation(original, decoded)) {
            std::cerr << "❌ Erreur de décodage à l’index " << count << " (perm index: " << index << ")\n";
            for (int i = 0; i < 8; ++i) {
                std::cerr << "  original[" << i << "] = " << ((original.corners >> (i * 4)) & 0xF)
                          << ", decoded[" << i << "] = " << ((decoded.corners >> (i * 4)) & 0xF)
                            << "\n";
            }
            assert(false);
        }

        ++count;

    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << "✅ Test réussi : toutes les " << count
                << " permutations sont correctes et sans collisions.\n";
}


bool compareEdgePermutation(const CubeState& a, const CubeState& b) {
    // Compare uniquement les 8 arêtes hors M-slice (indices 0-7)
    for (int i = 0; i < 8; ++i) {
        uint8_t ea = (a.edges >> (i * 4)) & 0xF;
        uint8_t eb = (b.edges >> (i * 4)) & 0xF;
        if (ea != eb)
            return false;
    }
    return true;
}

void testAllEdgePermutations() {
    std::array<uint8_t, 8> perm = {0, 1, 2, 3, 4, 5, 6, 7};
    std::unordered_set<uint32_t> seenIndexes;

    size_t count = 0;
    do {
        CubeState original{};
        original.edges = 0;

        // On place la permutation dans les 8 premières arêtes (hors M-slice)
        for (int i = 0; i < 8; ++i) {
            original.edges |= (uint64_t(perm[i]) & 0xF) << (i * 4);
        }
        // On met arbitrairement des valeurs fixes pour les M-slice (indices 8-11) pour ne pas avoir d'effet sur le test
        for (int i = 8; i < 12; ++i) {
            original.edges |= (uint64_t(i) & 0xF) << (i * 4);
        }

        uint32_t index = encodeUDSlicePermutation(original);

        // Vérifie qu’on n’a pas déjà vu cet index (pas de collisions)
        if (!seenIndexes.insert(index).second) {
            std::cerr << "❌ Collision détectée à l’index " << index << " pour la permutation :\n";
            for (int i = 0; i < 8; ++i) {
                std::cerr << "  perm[" << i << "] = " << +perm[i] << "\n";
            }
            assert(false);
        }

        CubeState decoded{};
        // On initialise aussi M-slice dans decoded pour éviter d'écraser sans le savoir
        for (int i = 8; i < 12; ++i) {
            decoded.edges |= (uint64_t(i) & 0xF) << (i * 4);
        }

        decodeUDSlicePermutation(decoded, index);

        if (!compareEdgePermutation(original, decoded)) {
            std::cerr << "❌ Erreur de décodage à l’index " << count << " (perm index: " << index << ")\n";
            for (int i = 0; i < 8; ++i) {
                std::cerr << "  original[" << i << "] = " << ((original.edges >> (i * 4)) & 0xF)
                          << ", decoded[" << i << "] = " << ((decoded.edges >> (i * 4)) & 0xF)
                            << "\n";
            }
            assert(false);
        }

        ++count;

    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << "✅ Test réussi : toutes les " << count
                << " permutations sont correctes et sans collisions.\n";
}






#include <iostream>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <cassert>

bool compareMSliceEdgePermutation(const CubeState& a, const CubeState& b) {
    static constexpr std::array<int, 4> M_SLICE_EDGES = {8, 9, 10, 11};
    for (int i = 0; i < 4; ++i) {
        uint8_t pa = (a.edges >> (M_SLICE_EDGES[i] * 4)) & 0xF;
        uint8_t pb = (b.edges >> (M_SLICE_EDGES[i] * 4)) & 0xF;
        if (pa != pb)
            return false;
    }
    return true;
}
void testAllMSliceEdgePermutations() {
    static constexpr int MSliceEdgesCount = 4;
    std::array<uint8_t, MSliceEdgesCount> perm = {0, 1, 2, 3};
    std::unordered_set<uint32_t> seenIndexes;

    static constexpr std::array<int, MSliceEdgesCount> M_SLICE_EDGES = {8, 9, 10, 11};

    size_t count = 0;
    do {
        CubeState original{};
        original.edges = 0;

        // Ici on écrit les vraies valeurs d'arêtes, pas juste les indices 0..3
        for (int i = 0; i < MSliceEdgesCount; ++i) {
            original.edges |= (uint64_t(M_SLICE_EDGES[perm[i]]) & 0xF) << (M_SLICE_EDGES[i] * 4);
        }

        uint32_t index = encodeMSliceEdgePermutation(original);

        // Vérifie collision d’index
        if (!seenIndexes.insert(index).second) {
            std::cerr << "❌ Collision détectée à l’index " << index << " pour la permutation :\n";
            for (int i = 0; i < MSliceEdgesCount; ++i) {
                std::cerr << "  perm[" << i << "] = " << +perm[i] << "\n";
            }
            assert(false);
        }

        CubeState decoded{};
        decodeMSliceEdgePermutation(decoded, index);

        if (!compareMSliceEdgePermutation(original, decoded)) {
            std::cerr << "❌ Erreur de décodage à l’index " << count << " (perm index: " << index << ")\n";
            for (int i = 0; i < MSliceEdgesCount; ++i) {
                std::cerr   << "  original[" << i << "] = " << ((original.edges >> (M_SLICE_EDGES[i] * 4)) & 0xF)
                            << ", decoded[" << i << "] = " << ((decoded.edges >> (M_SLICE_EDGES[i] * 4)) & 0xF)
                            << "\n";
            }
            assert(false);
        }

        ++count;

    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << "✅ Test réussi : toutes les " << count
                << " permutations M-Slice edges sont correctes et sans collisions.\n";
}