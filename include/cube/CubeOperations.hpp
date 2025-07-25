#pragma once
#include <cstdint>
#include "./CubeState.hpp"


inline uint8_t getPiece(uint64_t pieces, uint8_t index);

inline void setPiece(uint64_t &pieces, uint8_t index, uint8_t value);

inline void swapEdgeOrientation(uint64_t &edges, uint8_t i);

inline void setEdgeOrientation(uint64_t &edges, uint8_t i, uint8_t value);

inline void setCornerOrientation(uint64_t &corners, uint8_t i, uint8_t value);

inline uint8_t getCornerOrientation(uint64_t pieces, uint8_t i);

inline uint8_t getEdgeOrientation(uint64_t pieces, uint8_t i);

void cycle4Move(uint64_t &pieces, uint8_t p[4]);

void cycle4CornerOrientations(uint64_t &corners, uint8_t o[4], uint8_t cornerDeltas[4]);

void cycle4EdgeOrientations(uint64_t &edges, uint8_t o[4], bool swap);

void cycle4(
    CubeState &state,
    const uint8_t c[4],
    const uint8_t e[4],
    bool swapCorners = false,
    bool swapEdge = false
);



void cycle2CornerOrientations(uint64_t &corners, uint8_t a, uint8_t b);

void cycle2EdgeOrientations(uint64_t &edges, uint8_t a, uint8_t b);

inline void swap_piece(uint64_t &bits, uint8_t i, uint8_t j);

void swapCornerOrientation(
    CubeState &state,
    uint8_t i,
    uint8_t j
);

void swapEdgeOrientation(
    CubeState &state,
    uint8_t i,
    uint8_t j
);


void cycle2(
    CubeState &state,
    const uint8_t c[4],
    const uint8_t e[4],
    bool swapCorners = false,
    bool swapEdges = false
);