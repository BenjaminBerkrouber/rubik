#include "../../include/cube/Encoding.h"

// ===============================================================================================================================
// ===============================================================================================================================
// ==== KOCIEMBA ALGO ====
// ===============================================================================================================================
// ===============================================================================================================================

// ______________________________________________ G1 ______________________________________________


// =================================================================================
// ==== Corners Orientation Encoding ====
// =================================================================================

uint16_t encodeCornersOrientation(const CubeState& state) {
    uint16_t code = 0;
    for (int i = 0; i < 7; ++i) {
        uint8_t ori = (state.corners >> (32 + i * 2)) & 0x3;
        code = code * 3 + ori;
    }
    return code; // 3⁷ = 2187
}

void decodeCornersOrientation(CubeState& state, uint16_t code) {
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

uint16_t encodeEdgesOrientation(const CubeState& state) {
    uint16_t code = 0;
    for (int i = 0; i < 11; ++i) {
        uint8_t ori = (state.edges >> (48 + i)) & 0x1;
        code |= (ori << i);
    }
    return code; // 2¹¹ = 2048
}

void decodeEdgesOrientation(CubeState& state, uint16_t code) {
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

size_t encodeOrientationIndex(const CubeState& state) {
    uint16_t c = encodeCornersOrientation(state);
    uint16_t e = encodeEdgesOrientation(state);
    return static_cast<size_t>(c) * 2048 + e; // 3⁷ * 2¹¹
}

// =================================================================================
// ==== Slice Edges Encoding ====
// =================================================================================


constexpr uint16_t binomial(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    uint16_t res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - i + 1) / i;
    return res;
}

uint16_t encodeMSlice(const CubeState& state) {
    uint8_t slicePositions[4];
    int count = 0;

    for (int pos = 0; pos < 12; ++pos) {
        uint8_t edge = (state.edges >> (pos * 4)) & 0xF;
        if (edge >= 8 && edge <= 11) {
            slicePositions[count++] = pos;
        }
    }
    if (count != 4) return 0xFFFF;

    uint16_t index = 0;
    for (int i = 0; i < 4; ++i) {
        index += binomial(slicePositions[i], i + 1);
    }

    return 494 - index; // 494 = binomial(12, 4) - 1
}


// ______________________________________________ G2 ______________________________________________


// =================================================================================
// ==== Corners Permutation Encoding ====
// =================================================================================


uint32_t encodeCornerPermutation(const CubeState& state) {
    std::array<uint8_t, 8> perm;
    for (int i = 0; i < 8; ++i) {
        perm[i] = (state.corners >> (i * 4)) & 0xF;
    }

    uint32_t index = 0;
    std::array<bool, 8> used = {false};

    for (int i = 0; i < 8; ++i) {
        int count = 0;
        for (int j = 0; j < perm[i]; ++j) {
            if (!used[j])
                ++count;
        }
        index = index * (8 - i) + count;
        used[perm[i]] = true;
    }
    return index; // 8! = 40320
}

static constexpr int factorials[8] = {
    1, 1, 2, 6, 24, 120, 720, 5040
};

void decodeCornerPermutation(CubeState& state, uint32_t index) {
    std::array<uint8_t, 8> perm;
    std::array<uint8_t, 8> temp;
    for (int i = 0; i < 8; ++i)
        temp[i] = i;

    for (int i = 0; i < 8; ++i) {
        int f = factorials[7 - i];
        int selected = index / f;
        index %= f;

        perm[i] = temp[selected];
        for (int j = selected; j < 7 - i; ++j)
            temp[j] = temp[j + 1];
    }

    state.corners &= ~0xFFFFFFFFULL;
    for (int i = 0; i < 8; ++i) {
        state.corners |= (uint64_t(perm[i]) & 0xF) << (i * 4);
    }
}



// ==================================================================================
// ==== Edges UD Slice Permutation Encoding ====
// ==================================================================================


constexpr std::array<int, 4> M_SLICE_EDGES = {8, 9, 10, 11};
constexpr int NUM_EDGES = 12;

uint32_t encodeUDSlicePermutation(const CubeState& state) {
    std::array<uint8_t, NUM_EDGES> perm12;
    for (int i = 0; i < NUM_EDGES; ++i) {
        perm12[i] = (state.edges >> (i * 4)) & 0xF;
    }

    std::vector<uint8_t> perm8;
    for (int i = 0; i < NUM_EDGES; ++i) {
        if (std::find(M_SLICE_EDGES.begin(), M_SLICE_EDGES.end(), i) == M_SLICE_EDGES.end()) {
            perm8.push_back(perm12[i]);
        }
    }

    uint32_t index = 0;
    std::array<bool, 12> used = {false};

    for (int i = 0; i < 8; ++i) {
        int count = 0;
        for (int j = 0; j < perm8[i]; ++j) {
            if (!used[j])
                ++count;
        }
        index = index * (8 - i) + count;
        used[perm8[i]] = true;
    }

    return index; // 8! = 40320
}

void decodeUDSlicePermutation(CubeState& state, uint32_t index) {
    std::array<uint8_t, NUM_EDGES> perm12;
    for (int i = 0; i < NUM_EDGES; ++i) {
        perm12[i] = (state.edges >> (i * 4)) & 0xF;
    }

    std::array<uint8_t, 8> perm8;
    std::array<uint8_t, 8> temp = {0,1,2,3,4,5,6,7};
    for (int i = 0; i < 8; ++i) {
        int f = factorials[7 - i];
        int selected = index / f;
        index %= f;

        perm8[i] = temp[selected];
        for (int j = selected; j < 7 - i; ++j)
            temp[j] = temp[j + 1];
    }

    int pos = 0;
    for (int i = 0; i < NUM_EDGES; ++i) {
        if (std::find(M_SLICE_EDGES.begin(), M_SLICE_EDGES.end(), i) == M_SLICE_EDGES.end()) {
            perm12[i] = perm8[pos++];
        }
    }

    state.edges &= ~0xFFFFFFFFFFFFULL;
    for (int i = 0; i < NUM_EDGES; ++i) {
        state.edges |= (uint64_t(perm12[i]) & 0xF) << (i * 4);
    }
}



// ==================================================================================
// ==== Edges M Slice Permutation Encoding ====
// ==================================================================================


static constexpr int MSliceEdgesCount = 4;

uint32_t encodeMSliceEdgePermutation(const CubeState& state) {
    std::array<uint8_t, MSliceEdgesCount> perm;

    for (int i = 0; i < MSliceEdgesCount; ++i) {
        perm[i] = (state.edges >> (M_SLICE_EDGES[i] * 4)) & 0xF;
    }

    std::array<uint8_t, MSliceEdgesCount> permIndices;
    for (int i = 0; i < MSliceEdgesCount; ++i) {
        for (int j = 0; j < MSliceEdgesCount; ++j) {
            if (perm[i] == M_SLICE_EDGES[j]) {
                permIndices[i] = j;
                break;
            }
        }
    }

    uint32_t index = 0;
    std::array<bool, MSliceEdgesCount> used = {false};

    for (int i = 0; i < MSliceEdgesCount; ++i) {
        int count = 0;
        for (int j = 0; j < permIndices[i]; ++j) {
            if (!used[j])
                ++count;
        }
        index = index * (MSliceEdgesCount - i) + count;
        used[permIndices[i]] = true;
    }
    return index; // 4! = 24
}


void decodeMSliceEdgePermutation(CubeState& state, uint32_t index) {

    std::array<uint8_t, MSliceEdgesCount> perm;
    std::array<uint8_t, MSliceEdgesCount> temp = {0, 1, 2, 3};

    for (int i = 0; i < MSliceEdgesCount; ++i) {
        int f = factorials[MSliceEdgesCount - 1 - i];
        int selected = index / f;
        index %= f;

        perm[i] = temp[selected];
        for (int j = selected; j < MSliceEdgesCount - 1 - i; ++j)
            temp[j] = temp[j + 1];
    }
    for (int i = 0; i < MSliceEdgesCount; ++i) {
        state.edges &= ~(0xFULL << (M_SLICE_EDGES[i] * 4));
        state.edges |= (uint64_t(M_SLICE_EDGES[perm[i]]) & 0xF) << (M_SLICE_EDGES[i] * 4);
    }
}



