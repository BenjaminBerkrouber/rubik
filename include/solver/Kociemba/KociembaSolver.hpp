#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"


#include <vector>
#include <iostream>

#include "G1Solver.hpp"
#include "G2Solver.hpp"
#include "../ISolver.hpp"

/**
 * @class KociembaSolver
 * @brief Solver based on Kociemba’s two-phase algorithm.
 *
 * Implements the ISolver interface using a two-step approach:
 * - G1: reduce the cube to a defined subgroup.
 * - G2: solve from that subgroup to the fully solved state.
 */
class KociembaSolver : public ISolver {
    private:
        /**
        * @brief Reference to the cube state to be solved.
        */
        CubeState& _state;

        /**
        * @brief Spin manager to apply and track moves.
        */
        SpinManager _spinManager;

        /**
        * @brief Phase G1 solver.
        */
        G1Solver _g1Solver;

        /**
        * @brief Phase G2 solver.
        */
        G2Solver _g2Solver;

    public:
        /**
        * @brief Constructor for the Kociemba solver.
        * @param state Reference to the cube state to be solved.
        */
        KociembaSolver(CubeState& state);

        /**
        * @brief Destructor.
        */
        ~KociembaSolver();

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
        std::vector<std::pair<std::string, std::vector<SpinLst>>> getSolutionSteps() const override;
};

