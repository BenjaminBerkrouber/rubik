#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"

#include <vector>

/**
 * @class G1Solver
 * @brief Solves the first phase of Kociemba’s algorithm (G1).
 *
 * The G1 phase involves correctly orienting corners and edges,
 * and placing the edges into the middle (M) slice.
 * Uses an IDA* search with pruning tables.
 */
class G1Solver {
    private:
        /**
        * @brief Spin manager for applying and tracking moves.
        */
        SpinManager _spinManager;

        /**
        * @brief Pruning table for orientation of corners and edges.
        */
        std::vector<uint8_t> _pruningOrientation;

        /**
        * @brief Pruning table for edge positions in the M-slice.
        */
        std::vector<uint8_t> _pruningMSlice;

        /**
        * @brief Computed solution for G1 phase.
        */
        std::vector<SpinLst> _solution;

        /**
        * @brief Internal IDA* solver used to explore move sequences.
        *
        * @param state Current cube state.
        * @param maxDepth Maximum allowed depth for the current iteration.
        * @param depth Current recursive depth (default: 0).
        * @param hasLastMove Indicates whether the last move is available.
        * @param lastMove The last move performed.
        * @return true if a solution was found at this depth.
        */
        bool IDA(CubeState state, int maxDepth, int depth = 0, bool hasLastMove = false, SpinLst lastMove = SpinLst::U);

        /**
        * @brief Checks whether two moves are inverse of each other.
        * @param a First move.
        * @param b Second move.
        * @return true if both moves are inverses.
        */
        bool areInverseMoves(SpinLst a, SpinLst b);

    public:
        /**
        * @brief Constructs the G1 solver.
        */
        G1Solver();

        /**
        * @brief Destructor.
        */
        ~G1Solver() = default;

        /**
        * @brief Attempts to solve the cube's G1 phase.
        * @param state Initial cube state.
        * @return true if a solution was found.
        */
        bool solve(CubeState& state);

        /**
        * @brief Checks if required pruning tables are loaded and valid.
        * @return true if the tables are valid.
        */
        bool checkTable() const;

        /**
        * @brief Returns the solution found as a sequence of moves.
        * @return Vector of spins representing the G1 solution.
        */
        std::vector<SpinLst> getSolution() const;
};
