#pragma once

#include "../../cube/CubeState.hpp"
#include "../../cube/Encoding.h"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

#include "../Pruning/TableIO.hpp"
#include "./p2_move_tables.hpp"

#include <vector>


/**
 * @class G2Solver
 * @brief Solves the second phase (G2) of the Kociemba algorithm.
 *
 * The G2 phase permutes corners and central edges (M-slice and UD-slice),
 * and completes the cube. It uses IDA* search with pruning tables.
 */
class G2Solver {
    private:
        /**
        * @brief Move manager (SpinManager) for applying and tracking moves.
        */
        SpinManager _spinManager;

        /**
        * @brief Pruning table for corner permutation.
        */
        std::vector<uint8_t> _pruningCornersPermutation;

        /**
        * @brief Pruning table for M-slice edge permutation.
        */
        std::vector<uint8_t> _pruningMSlicePermutation;

        /**
        * @brief Pruning table for UD-slice edge permutation.
        */
        std::vector<uint8_t> _pruningUDSlicePermutation;

        /**
        * @brief Move tables for phase 2.
        */
        P2MoveTables p2Tables_;

        /**
        * @brief Computed move sequence for G2 solution.
        */
        std::vector<SpinLst> _solution;

        /**
        * @brief List of allowed moves in phase G2.
        *
        * Only U, D (all rotations) and double turns of other faces are allowed.
        */
        std::vector<SpinLst> _allowSpin = {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L2, SpinLst::R2, SpinLst::F2, SpinLst::B2
        };

        /**
        * @struct P2State
        * @brief Represents the state of the cube in terms of corner and edge permutations.
        */
        struct P2State {
            uint16_t cperm;   // 0..40319
            uint16_t msperm;  // 0..23
            uint16_t udperm;  // 0..40319
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
            const P2State& s,
            int g,
            int bound,
            bool hasLastMove,
            SpinLst lastMove
        );

        /**
        * @brief Checks if two moves are inverses of each other.
        * @param a First move.
        * @param b Second move.
        * @return true if the moves are inverses.
        */
        bool areInverseMoves(SpinLst a, SpinLst b);

    public:
        /**
        * @brief Constructs the G2 solver.
        */
        G2Solver();

        /**
        * @brief Destructor.
        */
        ~G2Solver() = default;

        /**
        * @brief Solves the G2 phase of the cube.
        * @param state Initial cube state.
        * @return true if a solution was found.
        */
        bool solve(CubeState& state);

        /**
        * @brief Checks if pruning tables are correctly loaded and valid.
        * @return true if tables are valid.
        */
        bool checkTable() const;

        /**
        * @brief Returns the computed solution as a sequence of moves.
        * @return Vector of SpinLst moves for the G2 phase.
        */
        std::vector<SpinLst> getSolution() const;
};
