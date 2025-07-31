#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"


#include <vector>

#include "G1Solver.hpp"
#include "G2Solver.hpp"
#include "../ISolver.hpp"

class KociembaSolver : public ISolver {
    private:
        CubeState& _state;
        G1Solver _g1Solver;
        G2Solver _g2Solver;

    public:
        KociembaSolver(CubeState &state);
        ~KociembaSolver();

        bool solve() override;
        std::vector<SpinLst> getSolution() const override;
};