#pragma once
#include <array>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include "../Cube.hpp"        // ta classe Cube

constexpr int NUM_ORIENTATIONS = 2187; // 3^7

using PruningTable = std::array<uint8_t, NUM_ORIENTATIONS>;

class PruningTableBase {

    protected:
        PruningTable table_;

    public:
        PruningTableBase();
        virtual ~PruningTableBase() = default;
        
        virtual void generateTable(Cube& cube) = 0;

        void writeToFile(const std::string& filename) const;
        bool readFromFile(const std::string& filename);

        uint8_t operator[](int index) const;

        int maxDepth() const;
};
