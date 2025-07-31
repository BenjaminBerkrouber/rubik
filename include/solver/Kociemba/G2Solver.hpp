#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"
#include "../Pruning/PruningTable.hpp"

#include <vector>

class G2Solver {
    private:
        SpinManager _spinManager;

        std::vector<uint8_t> _pruningCornersPermutation;
        std::vector<uint8_t> _pruningMSlicePermutation;
        std::vector<uint8_t> _pruningUDSlicePermutation;
        std::vector<SpinLst> _solution;

        std::vector<SpinLst> _allowSpin = {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
        };


        bool IDA(
            CubeState state,
            int maxDepth,
            std::unordered_map<CubeState, int> &visited,
            int depth = 0,
            bool hasLastMove = false,
            SpinLst lastMove = SpinLst::U
        );

        bool areInverseMoves(SpinLst a, SpinLst b);

    public:
        G2Solver();
        ~G2Solver() = default;

        bool solve(CubeState &state);
        std::vector<SpinLst> getSolution() const;
};