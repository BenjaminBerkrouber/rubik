#ifndef CUBE_ENCODING_H
# define CUBE_ENCODING_H

# include <vector>
# include <algorithm>
# include <array>
# include <cstddef>
# include <cstdint>

# include "./CubeState.hpp"


uint16_t encodeCornersOrientation(const CubeState& state);
void decodeCornersOrientation(CubeState& state, uint16_t code);

uint16_t encodeEdgesOrientation(const CubeState& state);
void decodeEdgesOrientation(CubeState& state, uint16_t code);

size_t encodeOrientationIndex(const CubeState& state);
uint16_t encodeMSlice(const CubeState& state);




uint32_t encodeCornerPermutation(const CubeState& state);
void decodeCornerPermutation(CubeState& state, uint32_t code);

uint32_t encodeUDSlicePermutation(const CubeState& state);
void decodeUDSlicePermutation(CubeState& state, uint32_t code);

uint32_t encodeMSliceEdgePermutation(const CubeState& state);
void    decodeMSliceEdgePermutation(CubeState& state, uint32_t code);

#endif // CUBE_ENCODING_H