#pragma once

#include "SpinFunctions.hpp"
#include "Spin.hpp"
#include "Constants.hpp"

/**
 * @typedef SpinFunction
 * @brief Function pointer type for applying a move to a CubeState.
 *
 * A SpinFunction is a pointer to a function that takes a CubeState reference
 * and applies a transformation (rotation of one face).
 */
using SpinFunction = void(*)(CubeState&);

/**
 * @var spinTable
 * @brief Lookup table of all possible spin functions.
 *
 * This table maps each value of the SpinLst enum to its corresponding
 * function that applies the move to a CubeState.
 * 
 * @see SpinLst
 * @see applyMove()
 */
extern SpinFunction spinTable[SPIN_COUNT];

/**
 * @brief Applies a move to the given CubeState.
 *
 * This function uses the spinTable to apply the appropriate transformation
 * to the cube state based on the move provided.
 *
 * @param state Reference to the CubeState to modify.
 * @param spin  The move to apply (enum value of SpinLst).
 */
inline void applyMove(CubeState& state, SpinLst spin) {
    spinTable[spin](state);
}
