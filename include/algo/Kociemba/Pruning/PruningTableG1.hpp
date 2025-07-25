
#pragma once

#include <array>
#include <vector>
#include <queue>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include "../../../Cube.hpp"
#include <algorithm>


class PruningTableG1 {

    private:

        std::array<uint8_t, 2187> corners_orientation_pruning_table;
        std::array<uint8_t, 4096> edges_orientation_pruning_table;
        std::array<uint8_t, 494> edges_slice_pruning_table;

        std::vector<SpinId> allowedSpins_ = {
            SpinId::U, SpinId::U2, SpinId::U_PRIME,
            SpinId::D, SpinId::D2, SpinId::D_PRIME,
            SpinId::L, SpinId::L2, SpinId::L_PRIME,
            SpinId::R, SpinId::R2, SpinId::R_PRIME,
            SpinId::F, SpinId::F2, SpinId::F_PRIME,
            SpinId::B, SpinId::B2, SpinId::B_PRIME
        };


        static constexpr int MAX_N = 12;
        static constexpr int MAX_R = 4;

        static int nCrTable[MAX_N + 1][MAX_R + 1];

        void init_nCrTable();
        static inline int nCr(int n, int r);



        
        std::array<uint8_t, 2187> generateCornersOrientationPruningTable();
        std::array<uint8_t, 4096> generateEdgesOrientationPruningTable();
        std::array<uint8_t, 494> generateEdgesSlicePruningTable();
        
                
    public:
        
        static int encodeCornersOrientation(const std::array<uint8_t, 8>& corners_orientation);
        static int encodeEgdeOrientation(const std::array<uint8_t, 12>& edges_orientation);
        static int encodeEdgesSlice(const std::array<uint8_t, 12>& edges_slice);
        static std::array<uint8_t, 8> decodeCornerOrientation(int index);
        static std::array<uint8_t, 12> decodeEdgeOrientation(int index);
        static std::array<uint8_t, 12> decodeEdgesSlice(int slice_index);
        const Cube &decodeCube(int index) const;
        int encodeCube(const Cube& cube) const;

        PruningTableG1();
        ~PruningTableG1();

        const std::array<uint8_t, 2187>& getCornersOrientationPruningTable() const;
        const std::array<uint8_t, 4096>& getEdgesOrientationPruningTable() const;
        const std::array<uint8_t, 494>& getEdgesSlicePruningTable() const;

        void generateTable();
};
