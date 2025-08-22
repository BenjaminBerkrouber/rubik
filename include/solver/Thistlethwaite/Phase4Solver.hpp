#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"

#include <vector>
#include "./IPhaseSolver.hpp"

class Phase4Solver : public IPhaseSolver {
    private:

        uint32_t encodage(const CubeState& state) const override {
            return encodeG3(state);
        }
        
    public:
        Phase4Solver() {
            pruning::io::load("./table/Thistlethwaite/g4_mirrorSpin.prune", _pruning, 0x01);
            _allowSpins = {
                SpinLst::U2, SpinLst::D2, SpinLst::L2, 
                SpinLst::R2, SpinLst::F2, SpinLst::B2
            };
            _maxDepth = 17;
            _pruningSize = 18501; // (4!^5/12)
        }

        ~Phase4Solver() = default;
};
