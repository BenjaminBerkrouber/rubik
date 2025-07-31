#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"
#include "../Pruning/PruningTable.hpp"

#include <vector>

class G1Solver {
    private:
        SpinManager _spinManager;

        std::vector<uint8_t> _pruningOrientation;
        std::vector<uint8_t> _pruningMSlice;
        std::vector<SpinLst> _solution;

        bool IDA(
            CubeState state,
            int maxDepth,
            int depth = 0,
            bool hasLastMove = false,
            SpinLst lastMove = SpinLst::U
        );

        bool areInverseMoves(SpinLst a, SpinLst b);

    public:
        G1Solver();
        ~G1Solver() = default;

        bool solve(CubeState &state);
        std::vector<SpinLst> getSolution() const;
};