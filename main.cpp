

#include "./include/cube/CubeState.hpp"
#include "./include/cube/SpinTable.hpp"
#include "./include/cube/Spin.hpp"
#include "./include/cube/SpinFunctions.hpp"
#include "./include/utils/CubeStateHelper.hpp"


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


int main() {

    // benshmark();
    // std::cout << "Static size (Cube):      " << sizeof(Cube) << " bytes" << std::endl;
    // std::cout << "Static size (CubeState): " << sizeof(CubeState) << " bytes" << std::endl;

    // Cube cube;
    CubeState cubestate;
    CubeStateHelper helper(cubestate);

    helper.printState();
    helper.printCube();

    
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