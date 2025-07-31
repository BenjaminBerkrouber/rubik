#ifndef CUBE_ENCODING_H
# define CUBE_ENCODING_H
# include <cstddef>
# include "./CubeState.hpp"


uint16_t encodeCornersOrientation(const CubeState& state);
void decodeCornersOrientation(CubeState& state, uint16_t code);

uint16_t encodeEdgesOrientation(const CubeState& state);
void decodeEdgesOrientation(CubeState& state, uint16_t code);

size_t encodeOrientationIndex(const CubeState& state);
uint16_t encodeMSlice(const CubeState& state);

#endif // CUBE_ENCODING_H