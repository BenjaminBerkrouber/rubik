

#include "./include/cube/CubeState.hpp"
#include "./include/cube/SpinTable.hpp"
#include "./include/cube/Spin.hpp"
#include "./include/cube/SpinFunctions.hpp"


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

    int N = 40000000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        cube.applySpin(SpinId::U);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        applyMove(cubestate, U);
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















void printEdgesBinary(uint64_t edges) {
    constexpr int totalNibbles = 12;

    std::cout << "Edge:                ";
    for (int i = 0; i < totalNibbles; ++i) {
        uint8_t nibble = (edges >> (i * 4)) & 0xF;
        // std::cout << "["
        //         << std::setw(2) << std::right << i
        //         << "] " << std::bitset<4>(nibble) 
        //         << " ("
        //         << std::setw(2) << std::right << static_cast<unsigned int>(nibble)
        //         << ")"
        //         << std::endl;
        std::cout << std::right << static_cast<unsigned int>(nibble)
                << " ";
    }

    std::cout << std::endl << "Edge Orientation:    ";
    for (int i = 48; i < 60; ++i) {
        std::cout << std::right << ((edges >> i) & 0x1)
                << " ";
    }
    std::cout << std::endl;
}

void printCornersBinary(uint64_t corners) {
    constexpr int totalCorners = 8;

    std::cout << "Corners:             ";
    for (int i = 0; i < totalCorners; ++i) {
        uint8_t corner = (corners >> (i * 4)) & 0xF; // 4 bits par corner
        std::cout << std::right << static_cast<unsigned int>(corner) << " ";
    }

    std::cout << std::endl << "Corners Orientation: ";
    for (int i = 0; i < totalCorners; ++i) {
        uint8_t orientation = (corners >> (32 + i * 2)) & 0x3; // 2 bits par orientation
        std::cout << std::right << static_cast<unsigned int>(orientation) << " ";
    }

    std::cout << std::endl;
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


// void fast_spinR(CubeState &cubestate) {
//     // swap edges
//     swapBits_xor(cubestate.edges, 4, 3);
//     swapBits_xor(cubestate.edges, 4, 7);
//     swapBits_xor(cubestate.edges, 4, 11);

//     // swap corners
//     swapBits_xor(cubestate.corners, 0, 3);
//     swapBits_xor(cubestate.corners, 0, 7);
//     swapBits_xor(cubestate.corners, 0, 4);

//     flipCornerOrientation(cubestate.corners, 0, 2);
//     flipCornerOrientation(cubestate.corners, 3, 1);
//     flipCornerOrientation(cubestate.corners, 7, 2);
//     flipCornerOrientation(cubestate.corners, 4, 1);
// }



int main() {

    benshmark();
    // std::cout << "Static size (Cube):      " << sizeof(Cube) << " bytes" << std::endl;
    // std::cout << "Static size (CubeState): " << sizeof(CubeState) << " bytes" << std::endl;

    // Cube cube;
    // CubeState cubestate;
    
    // CubePrinter printer(cube);

    // cube.applySpin(SpinId::R_PRIME);
    // applyMove(cubestate, R3);

    // std::cout << "================== BEFORE ==================" << std::endl;

    // printCubeSate(cube);

    // std::cout << std::endl << "================== FAST ==================" << std::endl;

    // printCornersBinary(cubestate.corners);
    // printEdgesBinary(cubestate.edges);



    return 0;
}