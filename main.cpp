#include "./include/Cube.hpp"
#include "./include/CubePrinter.hpp"
#include <chrono>


#include <random>
#include <iostream>


#include <vector>
#include <algorithm>
#include <utility>
#include <cstdint>
#include <array>
#include <queue>
#include <set>


#include <cstdint>

uint64_t encodeEdges() {
    uint64_t edges = 0;
    for (int i = 0; i < 12; ++i) {
        edges |= (static_cast<uint64_t>(i) & 0xF) << (4 * i);
    }
    return edges;
}


uint64_t encodeCorners() {
    uint64_t corners = 0;
    for (int i = 0; i < 8; ++i) {
        corners |= (static_cast<uint64_t>(i) & 0xF) << (i * 4);
    }
    return corners;
}


struct CubeState {
    uint64_t edges;
    uint64_t corners;
};

#include <iostream>
#include <bitset>





// void benshmark() {
//     Cube cube;
//     CubeState cubestate;

//     cubestate.edges = encodeEdges();

//     int N = 40000000;

//     auto start = std::chrono::high_resolution_clock::now();

//     for (int i = 0; i < N; ++i) {
//         cube.applySpin(SpinId::U);
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

//     start = std::chrono::high_resolution_clock::now();
//     for (int i = 0; i < N; ++i) {
//         fast_spinU(cubestate);
//     }
//     end = std::chrono::high_resolution_clock::now();
//     auto duration2_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

//     std::cout << "Duration for " << N << " spins:" << std::endl;

//     std::cout << "Last: " << std::endl 
//                             << std::setw(15) << duration_ns 
//                             << " ns " << std::endl
//                             << std::setw(15) << (duration_ns / 1e6) 
//                             << " ms" 
//                             << std::endl;

//     std::cout << "New:  " << std::endl 
//                             << std::setw(15) << duration2_ns 
//                             << " ns " << std::endl
//                             << std::setw(15) << (duration2_ns / 1e6) 
//                             << " ms" 
//                             << std::endl;
// }
















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




















inline void swapBits_xor(uint64_t &edges, int i, int j) {
    int shift_i = i * 4;
    int shift_j = j * 4;
    uint64_t mask = 0xFULL;

    uint64_t x = ((edges >> shift_i) & mask) ^ ((edges >> shift_j) & mask);

    if (x == 0) return;

    edges ^= (x << shift_i) | (x << shift_j);
}

inline void flipEdgeOrientation(uint64_t &edges, int i) {
    if (i < 0 || i >= 11) return;
    int bitPos = 48 + i;
    edges ^= (1ULL << bitPos);
}


inline void flipCornerOrientation(uint64_t &corners, int i, int delta) {
    if (i < 0 || i > 6) return;

    int shift = 32 + i * 2;
    uint8_t val = (corners >> shift) & 0b11;

    val = (val + delta) % 3;

    corners = (corners & ~(0b11ULL << shift)) | (static_cast<uint64_t>(val) << shift);

}






void fast_spinU(CubeState &cubestate) {
    // swap edges
    swapBits_xor(cubestate.edges, 0, 1);
    swapBits_xor(cubestate.edges, 0, 2);
    swapBits_xor(cubestate.edges, 0, 3);

    // swap corners
    swapBits_xor(cubestate.corners, 0, 1);
    swapBits_xor(cubestate.corners, 0, 2);
    swapBits_xor(cubestate.corners, 0, 3);

}

void fast_spinR(CubeState &cubestate) {
    // swap edges
    swapBits_xor(cubestate.edges, 4, 3);
    swapBits_xor(cubestate.edges, 4, 7);
    swapBits_xor(cubestate.edges, 4, 11);

    // swap corners
    swapBits_xor(cubestate.corners, 0, 3);
    swapBits_xor(cubestate.corners, 0, 7);
    swapBits_xor(cubestate.corners, 0, 4);

    flipCornerOrientation(cubestate.corners, 0, 2);
    flipCornerOrientation(cubestate.corners, 3, 1);
    flipCornerOrientation(cubestate.corners, 7, 2);
    flipCornerOrientation(cubestate.corners, 4, 1);
}



int main() {

    Cube cube;
    CubeState cubestate;
    CubePrinter printer(cube);

    cubestate.edges = encodeEdges();
    cubestate.corners = encodeCorners();


    // printCornersBinary(cubestate.corners);
    // std::cout << std::endl;

    // swapBits_xor(cubestate.corners, 0, 3);
    // printCornersBinary(cubestate.corners);
    // std::cout << std::endl;

    // swapBits_xor(cubestate.corners, 0, 7);
    // printCornersBinary(cubestate.corners);
    // std::cout << std::endl;

    // swapBits_xor(cubestate.corners, 0, 4);
    // printCornersBinary(cubestate.corners);
    // std::cout << std::endl;



    // flipCornerOrientation(cubestate.corners, 0, 2);


    cube.applySpin(SpinId::R);
    fast_spinR(cubestate);

    std::cout << "================== BEFORE ==================" << std::endl;

    printCubeSate(cube);

    std::cout << std::endl << "================== FAST ====================================" << std::endl;

    printCornersBinary(cubestate.corners);
    printEdgesBinary(cubestate.edges);


    return 0;
}