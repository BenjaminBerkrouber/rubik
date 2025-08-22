#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"


#include <vector>
#include <iostream>

#include "Phase1Solver.hpp"
#include "Phase2Solver.hpp"
#include "Phase3Solver.hpp"
#include "Phase4Solver.hpp"

#include "../ISolver.hpp"


class ThistlethwaiteSolver : public ISolver {
    private:
        /**
        * @brief Reference to the cube state to be solved.
        */
        CubeState& _state;

        /**
        * @brief Spin manager to apply and track moves.
        */
        SpinManager _spinManager;

        std::vector<IPhaseSolver*> _phaseSolvers;

    public:
        /**
        * @brief Constructor for the Kociemba solver.
        * @param state Reference to the cube state to be solved.
        */
        ThistlethwaiteSolver(CubeState& state);

        /**
        * @brief Destructor.
        */
        ~ThistlethwaiteSolver();

        /**
        * @brief Attempts to solve the cube using the Kociemba algorithm.
        * @return true if a solution is found, false otherwise.
        */
        bool solve() override;

        /**
        * @brief Checks if all necessary tables are loaded and valid.
        * @return true if all required data is available and valid, false otherwise.
        */
        bool checkTable() const override;

        /**
        * @brief Retrieves the computed solution as a list of spins.
        * @return Vector containing the moves needed to solve the cube.
        */
        std::vector<SpinLst> getSolution() const override;


        bool IDA(
            CubeState state,
            std::vector<SpinLst>& solution,
            std::vector<SpinLst> allowedMoves,
            int maxDepth,
            int depth,
            bool hasLastMove,
            SpinLst lastMove
        );

        std::vector<SpinLst> forburutG4();

};

