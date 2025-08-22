#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"

#include <vector>
#include "./IPhaseSolver.hpp"

class Phase1Solver : public IPhaseSolver {
    private:

        uint32_t encodage(const CubeState& state) const override {
            return encodeEdgesOrientation(state);
        }
        
    public:
        Phase1Solver() {
            pruning::io::load("./table/Thistlethwaite/g1_edge_orientation.prune", _pruning, 0x01);
            _allowSpins = {
                SpinLst::U, SpinLst::U2, SpinLst::U3,
                SpinLst::D, SpinLst::D2, SpinLst::D3,
                SpinLst::L, SpinLst::L2, SpinLst::L3,
                SpinLst::R, SpinLst::R2, SpinLst::R3,
                SpinLst::F, SpinLst::F2, SpinLst::F3,
                SpinLst::B, SpinLst::B2, SpinLst::B3
            };
            _maxDepth = 7;
            _pruningSize = 2048;
        }

        ~Phase1Solver() = default;
};
