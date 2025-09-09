#pragma once

#include "Spin.hpp"
#include "../cube/CubeState.hpp"
#include "../utils/Constants.hpp"
#include "../cube/CubeOperations.hpp"
#include <array>
#include <stdexcept>

/**
 * @struct SpinDefinition
 * @brief Defines a spin operation on a Rubik's Cube state.
 *
 * Contains a pointer to a cycle function (either cycle4 or cycle2),
 * arrays specifying the indices of corners and edges involved in the spin,
 * and booleans indicating if corners or edges are permuted (delta).
 */
struct SpinDefinition {
    /**
     * @brief Function pointer to the cycle operation applied during the spin.
     *
     * This function modifies the CubeState by cycling either 4 or 2 elements.
     * The function signature is:
     * void func(CubeState&, const uint8_t[4], const uint8_t[4], bool, bool);
     */
    void (*cycleFunc)(CubeState&, const uint8_t[4], const uint8_t[4], bool, bool);

    /**
     * @brief Indices of the 4 corners involved in the spin cycle.
     */
    uint8_t cornersIndex[4];

    /**
     * @brief Indices of the 4 edges involved in the spin cycle.
     */
    uint8_t edgeIndex[4];

    /**
     * @brief Indicates whether the spin permutes (deltas) the corners.
     */
    bool deltaCorners = false;

    /**
     * @brief Indicates whether the spin permutes (deltas) the edges.
     */
    bool deltaEdges = false;
};


/**
 * @class SpinManager
 * @brief Manages spin definitions and applies spins to the cube state.
 *
 * Contains an array of SpinDefinition entries corresponding to all possible spins.
 */
class SpinManager {
private:
    /**
     * @brief Array holding SpinDefinition entries for all spins.
     *
     * The array size is SPIN_COUNT, each corresponding to a spin identified by SpinLst.
     */
    std::array<SpinDefinition, SPIN_COUNT> _spinTable;

public:
    /**
     * @brief Constructs a SpinManager and initializes the spin table.
     */
    SpinManager();

    /**
     * @brief Default destructor.
     */
    ~SpinManager() = default;

    /**
     * @brief Applies a spin move to the given CubeState.
     *
     * Finds the SpinDefinition corresponding to the spin in the SpinLst enum
     * and invokes its cycle function to update the CubeState accordingly.
     *
     * @param state Reference to the CubeState to modify.
     * @param spin Spin identifier from SpinLst enum specifying which spin to apply.
     */
    void applyMove(CubeState& state, SpinLst spin);


    /**
     * @brief Retrieves the inverse of a given spin.
     *
     * The inverse of a spin is defined as the spin that undoes the effect of the original spin.
     * For example, if the original spin is "U", its inverse would be "U'".
     *
     * @param spin Spin identifier from SpinLst enum to get the inverse of.
     * @return The inverse SpinLst value.
     */
    SpinLst getInverseSpin(SpinLst spin) const;
};
