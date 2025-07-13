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
inline void pM(uint64_t &pieces, int i, int j) {
    int shift_i = i * 4;
    int shift_j = j * 4;
    uint64_t mask = 0xFULL;

    uint64_t x = ((pieces >> shift_i) & mask) ^ ((pieces >> shift_j) & mask);
    if (x == 0) return;

    pieces ^= (x << shift_i) | (x << shift_j);
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
 * @note If the index is out of range (i < 0 or i > 12), the function does nothing.
 */
inline void eOm(uint64_t &edges, int i) {
    if (i < 0 || i > 12) return;
    int bitPos = 48 + i;
    edges ^= (1ULL << bitPos);
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
 * @note Si l’indice `i` est hors limites (i < 0 ou i > 7), la fonction ne fait rien.
 */
inline void cOm(uint64_t &corners, int i, int delta) {
    if (i < 0 || i > 7) return;
    int shift = 32 + i * 2;
    uint8_t val = (corners >> shift) & 0b11;
    val = (val + delta) % 3;
    corners = (corners & ~(0b11ULL << shift)) | (static_cast<uint64_t>(val) << shift);
}
