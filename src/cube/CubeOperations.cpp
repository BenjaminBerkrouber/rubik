#include "../../include/cube/CubeOperations.hpp"

inline uint8_t getPiece(uint64_t pieces, uint8_t index) {
    return (pieces >> (index * 4)) & 0xF;
}

inline void setPiece(uint64_t &pieces, uint8_t index, uint8_t value) {
    uint64_t mask = 0xFULL << (index * 4);
    pieces = (pieces & ~mask) | (static_cast<uint64_t>(value) << (index * 4));
}

inline void swapEdgeOrientation(uint64_t &edges, uint8_t i) {
    if (i > 11) return;
    edges ^= (1ULL << (48 + i));
}

inline void setEdgeOrientation(uint64_t &edges, uint8_t i, uint8_t value) {
    if (i > 11) return;
    int shift = 48 + i;
    edges = (edges & ~(1ULL << shift)) | (static_cast<uint64_t>(value & 0x1) << shift);
}

inline void setCornerOrientation(uint64_t &corners, uint8_t i, uint8_t value) {
    if (i > 7) return;
    int shift = 32 + i * 2;
    corners = (corners & ~(0b11ULL << shift)) | (static_cast<uint64_t>(value % 3) << shift);
}

uint8_t getCornerOrientation(uint64_t pieces, uint8_t i) {
    return (pieces >> (32 + i * 2)) & 0x3;
}

uint8_t getEdgeOrientation(uint64_t pieces, uint8_t i) {
    return (pieces >> (48 + i)) & 0x1;
}

inline void cycle4Move(uint64_t &pieces, const uint8_t p[4]) {
    uint8_t temp = getPiece(pieces, p[3]);
    setPiece(pieces, p[3], getPiece(pieces, p[2]));
    setPiece(pieces, p[2], getPiece(pieces, p[1]));
    setPiece(pieces, p[1], getPiece(pieces, p[0]));
    setPiece(pieces, p[0], temp);
}

inline void cycle4CornerOrientations(uint64_t &corners, const uint8_t o[4], uint8_t cornerDeltas[4]) {
    uint8_t temp = getCornerOrientation(corners, o[3]);
    setCornerOrientation(corners, o[3], (getCornerOrientation(corners, o[2]) + cornerDeltas[3]));
    setCornerOrientation(corners, o[2], (getCornerOrientation(corners, o[1]) + cornerDeltas[2]));
    setCornerOrientation(corners, o[1], (getCornerOrientation(corners, o[0]) + cornerDeltas[1]));
    setCornerOrientation(corners, o[0], (temp + cornerDeltas[0]));
}

inline void cycle4EdgeOrientations(uint64_t &edges, const uint8_t o[4], bool swap) {
    uint8_t temp = getEdgeOrientation(edges, o[3]);
    setEdgeOrientation(edges, o[3], getEdgeOrientation(edges, o[2]));
    setEdgeOrientation(edges, o[2], getEdgeOrientation(edges, o[1]));
    setEdgeOrientation(edges, o[1], getEdgeOrientation(edges, o[0]));
    setEdgeOrientation(edges, o[0], temp);
    if (swap) {
        swapEdgeOrientation(edges, o[0]);
        swapEdgeOrientation(edges, o[1]);
        swapEdgeOrientation(edges, o[2]);
        swapEdgeOrientation(edges, o[3]);
    }
}

void cycle4(
    CubeState &state,
    const uint8_t c[4],
    const uint8_t e[4],
    bool swapCorners,
    bool swapEdges
) {
    uint8_t d[4];
    if (swapCorners) {
        d[0] = 2; d[1] = 1; d[2] = 2; d[3] = 1;
    } else {
        d[0] = 0; d[1] = 0; d[2] = 0; d[3] = 0;
    }
    cycle4CornerOrientations(state.corners, c, d);
    cycle4Move(state.corners, c);

    cycle4EdgeOrientations(state.edges, e, swapEdges);
    cycle4Move(state.edges, e);
}



void cycle2CornerOrientations(uint64_t &corners, uint8_t a, uint8_t b) {
    uint8_t temp = getCornerOrientation(corners, a);
    setCornerOrientation(corners, a, (getCornerOrientation(corners, b)));
    setCornerOrientation(corners, b, (temp));
}

void cycle2EdgeOrientations(uint64_t &edges, uint8_t a, uint8_t b) {
    uint8_t temp = getEdgeOrientation(edges, a);
    setEdgeOrientation(edges, a, getEdgeOrientation(edges, b));
    setEdgeOrientation(edges, b, temp);
}

#include <cstdint>

inline void swap_piece(uint64_t &bits, uint8_t i, uint8_t j) {
    uint8_t pi = getPiece(bits, i);
    uint8_t pj = getPiece(bits, j);
    setPiece(bits, i, pj);
    setPiece(bits, j, pi);
}

void swapCornerOrientation(
    CubeState &state,
    uint8_t i,
    uint8_t j
) {
    if (i > 7 || j > 7) return;
    uint8_t pi = getCornerOrientation(state.corners, i);
    uint8_t pj = getCornerOrientation(state.corners, j);
    setCornerOrientation(state.corners, i, pj);
    setCornerOrientation(state.corners, j, pi);
}
void swapEdgeOrientation(
    CubeState &state,
    uint8_t i,
    uint8_t j
) {
    if (i > 11 || j > 11) return;
    uint8_t pi = getEdgeOrientation(state.edges, i);
    uint8_t pj = getEdgeOrientation(state.edges, j);
    setEdgeOrientation(state.edges, i, pj);
    setEdgeOrientation(state.edges, j, pi);
}


void cycle2(
    CubeState &state,
    const uint8_t c[4],
    const uint8_t e[4],
    bool swapCorners,
    bool swapEdges
) {
    (void)swapCorners; // To avoid unused variable warning
    (void)swapEdges; // To avoid unused variable warning
    swapCornerOrientation(state, c[0], c[2]);
    swapCornerOrientation(state, c[1], c[3]);
    swap_piece(state.corners, c[0], c[2]);
    swap_piece(state.corners, c[1], c[3]);

    swapEdgeOrientation(state, e[0], e[2]);
    swapEdgeOrientation(state, e[1], e[3]);
    swap_piece(state.edges, e[0], e[2]);
    swap_piece(state.edges, e[1], e[3]);
}
