#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"

#include <iostream>
#include <vector>

class IPhaseSolver {
    protected:

        int _maxDepth = 0;
        size_t _pruningSize = 0;
        SpinManager _spinManager;

        std::vector<uint8_t> _pruning;
        std::vector<SpinLst> _allowSpins;
        std::vector<SpinLst> _solution;

        bool IDA(
            CubeState state,
            int maxDepth,
            int depth,
            bool hasLastMove,
            SpinLst lastMove
        );


        bool areInverseMoves(SpinLst a, SpinLst b);
        virtual uint32_t encodage(const CubeState& state) const = 0;

    public:
        
        IPhaseSolver() = default;
        virtual ~IPhaseSolver() = default;

        bool checkTable() const;

        bool solve(CubeState &state);

        std::vector<SpinLst> getSolution() const;
};