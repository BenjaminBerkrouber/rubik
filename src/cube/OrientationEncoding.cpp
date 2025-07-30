#include "../../include/cube/OrientationEncoding.hpp"

// =================================================================================
// ==== Corners Orientation Encoding ====
// =================================================================================

inline uint16_t encodeCornersOrientation(const CubeState& state) {
    uint16_t code = 0;
    for (int i = 0; i < 7; ++i) {
        uint8_t ori = (state.corners >> (32 + i * 2)) & 0x3; // 2 bits par coin
        code = code * 3 + ori;
    }
    return code;
}

inline void decodeCornersOrientation(CubeState& state, uint16_t code) {
    uint8_t total = 0;
    for (int i = 6; i >= 0; --i) {
        uint8_t ori = code % 3;
        code /= 3;
        total += ori;
        state.corners &= ~(uint64_t(0x3) << (32 + i * 2));
        state.corners |= uint64_t(ori) << (32 + i * 2);
    }

    uint8_t lastOri = (3 - (total % 3)) % 3;
    state.corners &= ~(uint64_t(0x3) << (32 + 7 * 2));
    state.corners |= uint64_t(lastOri) << (32 + 7 * 2);
}

// =================================================================================
// ==== Edges Orientation Encoding ====
// =================================================================================

inline uint16_t encodeEdgesOrientation(const CubeState& state) {
    uint16_t code = 0;
    for (int i = 0; i < 11; ++i) {
        uint8_t ori = (state.edges >> (48 + i)) & 0x1;
        code |= (ori << i);
    }
    return code;
}

inline void decodeEdgesOrientation(CubeState& state, uint16_t code) {
    uint8_t total = 0;
    for (int i = 0; i < 11; ++i) {
        uint8_t ori = (code >> i) & 0x1;
        total += ori;
        state.edges &= ~(uint64_t(1) << (48 + i));
        state.edges |= uint64_t(ori) << (48 + i);
    }
    uint8_t lastOri = (total % 2 == 0) ? 0 : 1;
    state.edges &= ~(uint64_t(1) << (48 + 11));
    state.edges |= uint64_t(lastOri) << (48 + 11);
}

// =================================================================================
// ==== Orientation Index Encoding ====
// =================================================================================


inline size_t encodeOrientationIndex(const CubeState& state) {
    uint16_t c = encodeCornersOrientation(state);
    uint16_t e = encodeEdgesOrientation(state);
    return static_cast<size_t>(c) * 2048 + e; // 3⁷ * 2¹¹
}


// =================================================================================
// ==== Slice Edges Encoding ====
// =================================================================================

#include <cstdint>

uint16_t encodeMSlice(const CubeState& state);

constexpr uint16_t binomial(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    uint16_t res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - i + 1) / i;
    return res;
}


uint16_t encodeMSlice(const CubeState& state) {
    uint16_t mask = 0;

    for (int pos = 0; pos < 12; ++pos) {
        uint8_t edge = (state.edges >> (pos * 4)) & 0xF;
        if (edge >= 8 && edge <= 11) {
            mask |= (1 << pos);
        }
    }

    uint16_t index = 0;
    int remaining = 4;

    for (int pos = 0; pos < 12 && remaining > 0; ++pos) {
        if (mask & (1 << pos)) {
            --remaining;
        } else {
            index += binomial(pos, remaining);
        }
    }

    return index;
}




