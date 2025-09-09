#ifndef CUBE_ENCODING_H
# define CUBE_ENCODING_H

# include <vector>
# include <algorithm>
# include <array>
# include <cstddef>
# include <cstdint>

# include "./CubeState.hpp"
# include "../spin/SpinManager.hpp"
# include "../utils/Constants.hpp"

// ===============================================================================================================================
// ===============================================================================================================================
// ==== KOCIEMBA ALGO ====
// ===============================================================================================================================
// ===============================================================================================================================

// ______________________________________________ G1 ______________________________________________


// =================================================================================
// ==== Corners Orientation Encoding ====
// =================================================================================


/**
 * @brief Encodes corner orientations into a unique integer.
 * @param state Cube state to encode.
 * @return uint16_t Encoded corner orientation code.
 */
uint16_t encodeCornersOrientation(const CubeState& state);

/**
 * @brief Decodes a corner orientation code into a cube state.
 * @param state Reference to the cube state to modify.
 * @param code Code to decode.
 */
void decodeCornersOrientation(CubeState& state, uint16_t code);


// =================================================================================
// ==== Edges Orientation Encoding ====
// =================================================================================


/**
 * @brief Encodes edge orientations into a unique integer.
 * @param state Cube state to encode.
 * @return uint16_t Encoded edge orientation code.
 */
uint16_t encodeEdgesOrientation(const CubeState& state);

/**
 * @brief Decodes an edge orientation code into a cube state.
 * @param state Reference to the cube state to modify.
 * @param code Code to decode.
 */
void decodeEdgesOrientation(CubeState& state, uint16_t code);


// =================================================================================
// ==== Orientation Index Encoding ====
// =================================================================================


/**
 * @brief Encodes both corner and edge orientations into a combined index.
 * @param state Cube state.
 * @return size_t Combined orientation index.
 */
size_t encodeOrientationIndex(const CubeState& state);

/**
 * @brief Decodes an orientation index into a cube state.
 * @param state Reference to the cube state to modify.
 * @param index Combined index to decode.
 */
void decodeOrientationIndex(CubeState& state, size_t index);


// =================================================================================
// ==== Slice Edges Encoding ====
// =================================================================================


/**
 * @brief Encodes M slice edges into a unique code.
 * @param state Cube state to encode.
 * @return uint16_t Encoded M slice edge code.
 */
uint16_t encodeMSlice(const CubeState& state);

/**
 * @brief Decodes M slice edge code into cube state.
 * @param state Reference to the cube state to modify.
 * @param code Code representing M slice edges.
 */
void decodeMSlice(CubeState& state, uint16_t code);


// ______________________________________________ G2 ______________________________________________


// =================================================================================
// ==== Corners Permutation Encoding ====
// =================================================================================


/**
 * @brief Encodes corner permutation into a unique integer.
 * @param state Cube state.
 * @return uint32_t Encoded corner permutation.
 */
uint32_t encodeCornerPermutation(const CubeState& state);

/**
 * @brief Decodes a corner permutation code into cube state.
 * @param state Reference to the cube state to modify.
 * @param code Encoded corner permutation.
 */
void decodeCornerPermutation(CubeState& state, uint32_t code);


// ==================================================================================
// ==== Edges UD Slice Permutation Encoding ====
// ==================================================================================


/**
 * @brief Encodes UD slice edge permutation.
 * @param state Cube state.
 * @return uint32_t Encoded UD slice edge permutation.
 */
uint32_t encodeUDSlicePermutation(const CubeState& state);

/**
 * @brief Decodes UD slice edge permutation into cube state.
 * @param state Reference to the cube state to modify.
 * @param code Encoded UD slice edge permutation.
 */
void decodeUDSlicePermutation(CubeState& state, uint32_t code);


// ==================================================================================
// ==== Edges M Slice Permutation Encoding ====
// ==================================================================================


/**
 * @brief Encodes M slice edge permutation.
 * @param state Cube state.
 * @return uint32_t Encoded M slice edge permutation.
 */
uint32_t encodeMSliceEdgePermutation(const CubeState& state);

/**
 * @brief Decodes M slice edge permutation into cube state.
 * @param state Reference to the cube state to modify.
 * @param code Encoded M slice edge permutation.
 */
void decodeMSliceEdgePermutation(CubeState& state, uint32_t code);


uint32_t encodageG2(const CubeState &state);
uint32_t encodeG3(const CubeState& state);
uint32_t encodeG4(const CubeState& state);

#endif // CUBE_ENCODING_H