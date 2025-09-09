#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"
#include "./p1_move_tables.hpp"

#include <vector>

#include <array>
#include <algorithm>
#include <stdexcept>

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
        * @brief Move tables for phase 1.
        */
        MoveTables p1Tables_;

        /**
        * @brief Computed solution for G1 phase.
        */
        std::vector<SpinLst> _solution;

        bool _mode;

        /**
        * @struct P1State
        * @brief Represents the state of the cube in terms of orientations and M-slice edges.
        */
        struct P1State {
            uint16_t twist;   // encodeCornersOrientation(state)  ∈ [0..2186]
            uint16_t flip;    // encodeEdgesOrientation(state)     ∈ [0..2047]
            uint16_t mslice;  // encodeMSlice(state)               ∈ [0..494]
        };


        /**
        * @brief Internal IDA* solver used to explore move sequences.
        *
        * @param s Current state in terms of orientations and M-slice edges.
        * @param g Current depth in the search tree.
        * @param bound Current cost bound for the search.
        * @param hasLastMove Indicates if there was a last move made.
        * @param lastMove The last move made in the search.
        * @return true if a solution was found within the given bound.
        */
        bool IDA(
            const P1State& s,
            int g,
            int bound,
            bool hasLastMove,
            SpinLst lastMove
        );

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
        bool solve(CubeState& state, bool mode);

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
