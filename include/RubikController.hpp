#pragma once

#include "cube/CubeState.hpp"
#include "spin/SpinManager.hpp"
#include "parser/Parser.hpp"
#include "engine/IEngine.hpp"
#include "solver/ISolver.hpp"

#include <iostream>

/**
 * @class RubikController
 * @brief Central controller that coordinates the main components of the Rubik's Cube application.
 *
 * This class acts as the brain of the program, managing and orchestrating the core components:
 * - CubeState (state representation)
 * - Parser (parsing input moves)
 * - SpinManager (applying moves to the cube)
 * - ISolver (abstract interface for solving the cube)
 * - IEngine (abstract interface for rendering or printing the cube)
 *
 * The controller provides utility methods to parse input, apply shuffles, display the cube,
 * and invoke the solving algorithm.
 */
class RubikController {
    private:
        CubeState       _cubeState;     /**< Represents the current state of the Rubik's Cube */
        Parser          _parser;        /**< Parses input spin sequences */
        SpinManager     _spinManager;   /**< Applies spin moves to the cube */
        ISolver         *_solver = nullptr; /**< Pointer to the solver interface */
        IEngine         *_engine = nullptr; /**< Pointer to the engine interface (display handler) */

        /**
        * @brief Applies a random shuffle of the cube.
        *
        * @param count Number of random spins to apply
        * @return true if shuffle succeeded, false otherwise
        */
        ParseResult randomSuffle(int count);

    public:
        /**
        * @brief Constructs a RubikController and initializes all components.
        */
        RubikController();
        
        /**
        * @brief Default destructor.
        */
        ~RubikController() = default;

        /**
        * @brief Parses and applies a string of moves or applies a random shuffle based on environment variable.
        *
        * If the environment variable "RUBIK_MODE" is set to "RANDOM", applies a random shuffle.
        * Otherwise, parses and applies the input moves.
        *
        * @param input A string representing the sequence of spins (ignored if random shuffle)
        * @return true if the operation succeeds, false otherwise
        */
        ParseResult parse(const std::string& input);

        /**
        * @brief Applies a shuffle to the cube (used for randomizing).
        */
        void applySuffle();

        /**
        * @brief Displays or prints the current state of the cube using the selected engine.
        */
        void print() const;

        /**
        * @brief Solves the cube using the selected solving algorithm.
        */
        void solve();

        /**
         * @brief Resets the RubikController to its initial state.
         *
         * This method reinitializes the cube state, clears any parsing results,
         * and safely deletes and recreates the solver and engine components.
         * After calling this function, the controller will be in a clean state,
         * ready for new operations.
         */
        void reset();

        std::vector<SpinLst> getShuffle() const;

        std::vector<SpinLst> getSolution() const;

};