#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"

#include <vector>
#include "./IPhaseSolver.hpp"

class Phase3Solver : public IPhaseSolver {
    private:

        uint32_t encodage(const CubeState& state) const override {
            return encodeG3(state);
        }
        
    public:
        Phase3Solver() {
            pruning::io::load("./table/Thistlethwaite/g3_group_edgeCornes_parity.prune", _pruning, 0x01);
            _allowSpins = {
                SpinLst::U, SpinLst::U2, SpinLst::U3,
                SpinLst::D, SpinLst::D2, SpinLst::D3,
                SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
            };
            _maxDepth = 15;
            _pruningSize = 29400; // C(8, 4)^2 * 2 * 3 = 29400 
            // 70 (groupement coins) × 70 (groupement arêtes) × 2 (parité) × 3 (torsion) = 29 400 états

        }

        ~Phase3Solver() = default;
};
