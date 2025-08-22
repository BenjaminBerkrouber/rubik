#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"

#include <vector>
#include "./IPhaseSolver.hpp"

class Phase2Solver : public IPhaseSolver {
    private:

        uint32_t encodage(const CubeState& state) const override {
            return encodageG2(state);
        }
        
    public:
        Phase2Solver() {
            pruning::io::load("./table/Thistlethwaite/g2_corner_orientation_mSlice.prune", _pruning, 0x01);
            _allowSpins = {
                SpinLst::U, SpinLst::U2, SpinLst::U3,
                SpinLst::D, SpinLst::D2, SpinLst::D3,
                SpinLst::L, SpinLst::L2, SpinLst::L3,
                SpinLst::R, SpinLst::R2, SpinLst::R3,
                SpinLst::F2, SpinLst::B2
            };
            _maxDepth = 13;
            _pruningSize = 2187 * 495; // 3⁷ * C(12, 4) = 1082565
        }

        ~Phase2Solver() = default;
};
