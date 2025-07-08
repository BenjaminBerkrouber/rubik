#pragma once
#include <cstdint>

inline void pM(uint64_t &edges, int i, int j) {
    int shift_i = i * 4;
    int shift_j = j * 4;
    uint64_t mask = 0xFULL;

    uint64_t x = ((edges >> shift_i) & mask) ^ ((edges >> shift_j) & mask);
    if (x == 0) return;

    edges ^= (x << shift_i) | (x << shift_j);
}

inline void eOm(uint64_t &edges, int i) {
    if (i < 0 || i >= 11) return;
    int bitPos = 48 + i;
    edges ^= (1ULL << bitPos);
}

inline void cOm(uint64_t &corners, int i, int delta) {
    if (i < 0 || i > 6) return;
    int shift = 32 + i * 2;
    uint8_t val = (corners >> shift) & 0b11;
    val = (val + delta) % 3;
    corners = (corners & ~(0b11ULL << shift)) | (static_cast<uint64_t>(val) << shift);
}
