#pragma once

#include "Spin.hpp"
#include "../cube/CubeState.hpp"
#include "../utils/Constants.hpp"
#include "../cube/CubeOperations.hpp"
#include <array>
#include <stdexcept>

struct SpinDefinition {
    void (*cycleFunc)(CubeState&, const uint8_t[4],const uint8_t[4], bool, bool);
    uint8_t cornersIndex[4];
    uint8_t edgeIndex[4];
    bool deltaCorners = false;
    bool deltaEdges = false;
};


class SpinManager {
    private:
        std::array<SpinDefinition, SPIN_COUNT> _spinTable;

    public:
        SpinManager();
        ~SpinManager() = default;

        void applyMove(CubeState& state, SpinLst spin);
};