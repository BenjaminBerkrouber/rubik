#pragma once
#include <cstdint>

/**
 * @brief Swaps two pieces in a compact 64-bit representation of a Rubik’s Cube.
 *
 * This function exchanges the 4-bit values located at positions `i` and `j` within a 64-bit integer.
 * Each position represents a Rubik’s Cube piece (either a corner or an edge), encoded using 4 bits.
 *
 * The entire cube state is stored in a single `uint64_t`, allowing up to 16 pieces to be represented
 * (16 positions × 4 bits = 64 bits). The 4-bit encoding per position typically represents the identity
 * and/or orientation of the piece.
 *
 * @param edges Reference to the 64-bit integer containing the pieces to swap.
 * @param i Index of the first position to swap (0 to 15).
 * @param j Index of the second position to swap (0 to 15).
 *
 * @note If both positions contain the same 4-bit value, no swap is performed.
 */
inline void pM(uint64_t &pieces, uint8_t i, uint8_t j) {
    int shift_i = i * 4;
    int shift_j = j * 4;
    uint64_t mask = 0xFULL;

    uint64_t x = ((pieces >> shift_i) & mask) ^ ((pieces >> shift_j) & mask);
    if (x == 0) return;

    pieces ^= (x << shift_i) | (x << shift_j);
}

inline uint8_t getPiece(uint64_t pieces, uint8_t index) {
    return (pieces >> (index * 4)) & 0xF;
}

inline void setPiece(uint64_t &pieces, uint8_t index, uint8_t value) {
    uint64_t mask = 0xFULL << (index * 4);
    pieces = (pieces & ~mask) | (static_cast<uint64_t>(value) << (index * 4));
}




/**
 * @brief Flips the orientation bit of an edge piece in a compact Rubik’s Cube representation.
 *
 * This function toggles (inverts) the orientation of a single edge piece in the 64-bit integer
 * representing the Rubik’s Cube state. Edge orientations are stored using 1 bit per edge,
 * located in bits 48 to 59 (i.e., 12 bits max for 12 edges).
 *
 * An edge piece can have one of two orientations: 0 or 1. This function flips the bit corresponding
 * to the edge at index `i`, effectively changing its orientation.
 *
 * This operation is specific to edge orientation moves (edgeOrientationMove).
 *
 * @param edges Reference to the 64-bit integer containing the edge orientation data.
 * @param i Index of the edge whose orientation should be flipped (must be in [0, 12]).
 *
 * @note If the index is out of range (i > 11), the function does nothing.
 */
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

inline void cycle4Move(uint64_t &pieces, uint8_t p[4]) {
    uint8_t temp = getPiece(pieces, p[3]);
    setPiece(pieces, p[3], getPiece(pieces, p[2]));
    setPiece(pieces, p[2], getPiece(pieces, p[1]));
    setPiece(pieces, p[1], getPiece(pieces, p[0]));
    setPiece(pieces, p[0], temp);
}

inline void cycle4CornerOrientations(uint64_t &corners, uint8_t o[4], uint8_t cornerDeltas[4]) {
    uint8_t temp = getCornerOrientation(corners, o[3]);
    setCornerOrientation(corners, o[3], (getCornerOrientation(corners, o[2]) + cornerDeltas[3]));
    setCornerOrientation(corners, o[2], (getCornerOrientation(corners, o[1]) + cornerDeltas[2]));
    setCornerOrientation(corners, o[1], (getCornerOrientation(corners, o[0]) + cornerDeltas[1]));
    setCornerOrientation(corners, o[0], (temp + cornerDeltas[0]));
}

inline void cycle4EdgeOrientations(uint64_t &edges, uint8_t o[4], bool swap) {
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
    uint8_t c[4],
    uint8_t e[4],
    bool swapCorners = false,
    bool swapEdges = false
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
    uint8_t c[4],
    uint8_t e[4]
) {
    swapCornerOrientation(state, c[0], c[2]);
    swapCornerOrientation(state, c[1], c[3]);
    swap_piece(state.corners, c[0], c[2]);
    swap_piece(state.corners, c[1], c[3]);

    swapEdgeOrientation(state, e[0], e[2]);
    swapEdgeOrientation(state, e[1], e[3]);
    swap_piece(state.edges, e[0], e[2]);
    swap_piece(state.edges, e[1], e[3]);
}

/**
 * @brief Modifie l’orientation d’une pièce "corner" dans une représentation compacte du Rubik’s Cube.
 *
 * Cette fonction met à jour l’orientation d’un coin (corner) dans un entier 64 bits.
 * Chaque coin est encodé sur 2 bits, ce qui permet de représenter 3 états possibles : 0, 1 ou 2.
 *
 * L’orientation est incrémentée de `delta` (généralement 1 ou 2), puis normalisée modulo 3,
 * afin de toujours rester dans l’intervalle [0, 1, 2].
 *
 * Les bits d’orientation des coins commencent à la position 32, donc les coins occupent les bits
 * 32 à 47 (8 coins × 2 bits = 16 bits).
 *
 * @param corners Référence vers l’entier 64 bits contenant les données d’orientation des coins.
 * @param i Indice du coin dont l’orientation doit être modifiée (entre 0 et 7).
 * @param delta Valeur à ajouter à l’orientation actuelle (modulo 3), généralement 1 ou 2.
 *
 * @note Si l’indice `i` est hors limites (i > 7), la fonction ne fait rien.
 */
inline void cOm(uint64_t &corners, int i, int delta) {
    if (i < 0 || i > 7) return;
    int shift = 32 + i * 2;
    uint8_t val = (corners >> shift) & 0b11;
    val = (val + delta) % 3;
    corners = (corners & ~(0b11ULL << shift)) | (static_cast<uint64_t>(val) << shift);
}
