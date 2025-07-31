#pragma once

/**
 * @class ISolver
 * @brief Abstract interface for Rubik’s Cube solvers.
 *
 * Defines the core methods any cube solver must implement: solving, table verification, and retrieving the solution.
 */
class ISolver {
    protected:
        /**
        * @brief The cube state to solve.
        */
        CubeState _state;

    public:
        /**
        * @brief Attempts to solve the cube.
        * @return true if a solution was found, false otherwise.
        */
        virtual bool solve() = 0;

        /**
        * @brief Checks whether the necessary pruning or lookup tables are loaded and valid.
        * @return true if the tables are valid, false otherwise.
        */
        virtual bool checkTable() const = 0;

        /**
        * @brief Retrieves the solution as a list of spins/moves.
        * @return Vector containing the moves to solve the cube.
        */
        virtual std::vector<SpinLst> getSolution() const = 0;

        /**
        * @brief Default virtual destructor.
        */
        virtual ~ISolver() = default;
};
