#pragma once

#include "../utils/Constants.hpp"
#include <cstdint>
#include <functional>

/**
 * @brief Represents the complete state of a Rubik's Cube using compact bit-level encoding.
 *
 * The `CubeState` struct stores both the position and orientation of all corner and edge pieces 
 * of a Rubik's Cube in two 64-bit unsigned integers.
 *
 * - `edges` encodes:
 *   - The position of 12 edge pieces using 4 bits each (total: 48 bits), stored in bits 0 to 47.
 *   - The orientation of 12 edge pieces using 1 bit each (total: 12 bits), stored in bits 48 to 59.
 *   - Remaining bits (60 to 63) are unused (padding).
 *
 * - `corners` encodes:
 *   - The position of 8 corner pieces using 4 bits each (total: 32 bits), stored in bits 0 to 31.
 *   - The orientation of 8 corner pieces using 2 bits each (total: 16 bits), stored in bits 32 to 47.
 *   - Remaining bits (48 to 63) are unused (padding).
 *
 * This compact representation allows fast operations and memory efficiency in algorithms manipulating cube states.
 */
struct CubeState
{
    uint64_t edges = EDGES_SOLVED_STATE;
    uint64_t corners = CORNERS_SOLVED_STATE;

    bool isSolved() const {
        return edges == EDGES_SOLVED_STATE && corners == CORNERS_SOLVED_STATE;
    }

    bool operator==(const CubeState& other) const {
        return edges == other.edges && corners == other.corners;
    }
};

/**
 * @namespace std
 * @brief Specialization of std::hash for the CubeState structure.
 *
 * This specialization allows CubeState to be used as a key in hash-based
 * containers like `std::unordered_map` or `std::unordered_set`.
 */

namespace std {

    /**
    * @struct hash<CubeState>
    * @brief Custom hash function for CubeState.
    *
    * This function combines the `edges` and `corners` fields of the CubeState structure
    * to produce a unique hash value suitable for unordered containers.
    */
    template<>
    struct hash<CubeState> {
        /**
        * @brief Computes a hash value for a given CubeState instance.
        * 
        * @param cs Constant reference to the CubeState object to be hashed.
        * @return size_t The resulting hash value.
        */
        size_t operator()(const CubeState& cs) const noexcept {
            return cs.edges ^ (cs.corners + 0x9e3779b9 + (cs.edges << 6) + (cs.edges >> 2));
        }
    }; // namespace hash<CubeState>

} // namespace std

