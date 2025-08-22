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

void decodeOrientationIndex(CubeState& state, size_t index) {
    uint16_t e = index % 2048;
    uint16_t c = index / 2048;
    decodeEdgesOrientation(state, e);
    decodeCornersOrientation(state, c);
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


void decodeMSlice(CubeState& state, uint16_t code) {
    uint8_t slicePositions[4];
    int count = 0;

    for (int pos = 0; pos < 12; ++pos) {
        uint8_t edge = (state.edges >> (pos * 4)) & 0xF;
        if (edge >= 8 && edge <= 11) {
            slicePositions[count++] = pos;
        }
    }
    if (count != 4) return;

    uint16_t index = 494 - code;
    for (int i = 3; i >= 0; --i) {
        int binom = binomial(12 - i, i + 1);
        int selected = index / binom;
        index %= binom;

        state.edges &= ~(0xFULL << (slicePositions[i] * 4));
        state.edges |= (uint64_t(selected + 8) & 0xF) << (slicePositions[i] * 4);
    }
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

static constexpr int factorials[10] = {
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
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

uint32_t encodageG2(const CubeState& state) {
    uint16_t cornersOri = encodeCornersOrientation(state);
    uint16_t mSlice = encodeMSlice(state);
    return cornersOri * 495 + mSlice; // 3⁷ * C(12, 4) = 1081065
}







uint16_t encodeCornerUDParity(const CubeState& state) {
    std::array<uint8_t, 8> cornerIDs;
    for (int i = 0; i < 8; ++i)
        cornerIDs[i] = (state.corners >> (i * 4)) & 0xF;  // 4 bits + masque 0xF = 4 bits

    std::array<uint8_t, 4> udGroup;
    int count = 0;
    for (int pos = 0; pos < 8; ++pos) {
        uint8_t cornerID = cornerIDs[pos];
        if (cornerID < 4) { // URF, UFL, ULB, UBR
            udGroup[count++] = pos;
        }
    }

    if (count != 4) return 0xFFFF;


    uint16_t index = 0;
    for (int i = 0; i < 4; ++i)
        index += binomial(udGroup[i], i + 1);

    return index;
}


uint16_t encodeEdgeUDParity(const CubeState& state) {
    std::array<uint8_t, 12> edgePos;
    for (int i = 0; i < 12; ++i)
        edgePos[i] = (state.edges >> (i * 4)) & 0xF;

    std::array<uint8_t, 4> udGroup;
    int count = 0;
    for (int i = 0; i < 12 && count < 4; ++i) {
        if (edgePos[i] <= 3) { // edge UF, UR, UL, UB
            udGroup[count++] = i; // on stocke la *position*
        }
    }
    if (count != 4) return 0xFFFF;

    uint16_t index = 0;
    for (int i = 0; i < 4; ++i)
        index += binomial(udGroup[i], i + 1);

    return index;
}

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cassert>


#include <array>
#include <cstdint>

template <size_t N>
int parityOfPermutation(const std::array<uint8_t, N>& perm) {
    int parity = 0;
    for (size_t i = 0; i < N - 1; ++i) {
        for (size_t j = i + 1; j < N; ++j) {
            if (perm[i] > perm[j])
                parity ^= 1;
        }
    }
    return parity;
}

uint8_t encodeCornerEdgeParity(const CubeState& state) {
    std::array<uint8_t, 8> cornerIDs;
    for (int i = 0; i < 8; ++i)
        cornerIDs[i] = (state.corners >> (i * 4)) & 0xF;
    int cornerParity = parityOfPermutation(cornerIDs);

    return cornerParity; // cornersPartity == edgeParity
}


uint8_t encodeTwistIndex(const CubeState& state) {
    std::array<uint8_t, 8> cornerIDs;
    for (int i = 0; i < 8; ++i)
        cornerIDs[i] = (state.corners >> (i * 4)) & 0xF;

    // On récupère les IDs des coins situés en positions URF, UFL, ULB, UBR (0 à 3)
    std::array<uint8_t, 4> upperIDs = {
        cornerIDs[0], // coin en position URF
        cornerIDs[1], // coin en position UFL
        cornerIDs[2], // coin en position ULB
        cornerIDs[3]  // coin en position UBR
    };

    // Lehmer code mod 3
    uint8_t index = 0;
    std::array<bool, 8> used = {false}; // Doit couvrir tous les IDs de coin (0–7)

    for (int i = 0; i < 4; ++i) {
        uint8_t count = 0;
        for (int j = 0; j < upperIDs[i]; ++j)
            if (!used[j]) ++count;

        index += count * factorials[3 - i];
        used[upperIDs[i]] = true;
    }

    return index % 3;
}




uint32_t encodeG3(const CubeState& state) {
    uint16_t corners = encodeCornerUDParity(state);  // ∈ [0, 69] // CHECK OK
    uint16_t edges = encodeEdgeUDParity(state);      // ∈ [0, 69] // CHECK OK
    uint8_t parity = encodeCornerEdgeParity(state);  // ∈ [0, 1]  // CHECK OK
    uint8_t twist = encodeTwistIndex(state);         // ∈ [0, 2]

    return (((corners * 70 + edges) * 2 + parity) * 3) + twist; // ∈ [0, 29400] MAIS retourn 2900 etats
}


























// ==== Hasher pour CubeState afin d’utiliser unordered_set ====
struct CubeStateHash {
  std::size_t operator()(const CubeState& s) const noexcept {
    // mélange simple 128->64
    uint64_t x = s.edges ^ (s.corners * 0x9e3779b97f4a7c15ULL);
    // finalisation style splitmix
    x ^= x >> 30; x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27; x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return static_cast<std::size_t>(x);
  }
};

// === Helpers d’accès aux positions (adaptés à ton packing) ===
inline int cornerCubieAt(const CubeState& s, int slot) {
  // 4 bits par slot, LSB-first (bits 0..31)
  return int((s.corners >> (slot * 4)) & 0xF);
}
inline int edgeCubieAt(const CubeState& s, int slot) {
  // 4 bits par slot, LSB-first (bits 0..47)
  return int((s.edges >> (slot * 4)) & 0xF);
}

// === Ranking S4 (Lehmer) : 4! = 24 ===
inline uint8_t rankS4(const std::array<int,4>& p) {
  uint8_t code = 0;
  for (int i = 0; i < 4; ++i) {
    int c = 0;
    for (int j = i + 1; j < 4; ++j) if (p[j] < p[i]) ++c;
    code = uint8_t(code * (4 - i) + c);
  }
  return code; // 0..23
}

// === Clé G4 (5 permutations S4) ===
struct G4Key { uint8_t cU, cD, eU, eM, eD; };

inline G4Key extractG4Key(const CubeState& s) {
  // Slots (selon tes enums)
  static constexpr std::array<int,4> U_CORNER_SLOTS = { URF, UFL, ULB, UBR };
  static constexpr std::array<int,4> D_CORNER_SLOTS = { DFR, DLF, DBL, DRB };

  static constexpr std::array<int,4> U_EDGE_SLOTS   = { UR, UF, UL, UB };
  static constexpr std::array<int,4> M_EDGE_SLOTS   = { FR, FL, BL, BR };
  static constexpr std::array<int,4> D_EDGE_SLOTS   = { DR, DF, DL, DB };

  // IDs (identités) attendus par tétrade
  static constexpr std::array<int,4> U_CORNER_IDS = { URF, UFL, ULB, UBR };
  static constexpr std::array<int,4> D_CORNER_IDS = { DFR, DLF, DBL, DRB };
  static constexpr std::array<int,4> U_EDGE_IDS   = { UR, UF, UL, UB };
  static constexpr std::array<int,4> M_EDGE_IDS   = { FR, FL, BL, BR };
  static constexpr std::array<int,4> D_EDGE_IDS   = { DR, DF, DL, DB };

  auto makeInv = [](const std::array<int,4>& ids) {
    std::array<int,12> inv{}; inv.fill(-1);
    for (int i = 0; i < 4; ++i) inv[ids[i]] = i;
    return inv;
  };
  static const std::array<int,12> INV_UC = makeInv(U_CORNER_IDS);
  static const std::array<int,12> INV_DC = makeInv(D_CORNER_IDS);
  static const std::array<int,12> INV_UE = makeInv(U_EDGE_IDS);
  static const std::array<int,12> INV_ME = makeInv(M_EDGE_IDS);
  static const std::array<int,12> INV_DE = makeInv(D_EDGE_IDS);

  auto permCorners = [&](const std::array<int,4>& slotOrder,
                         const std::array<int,12>& invMap) {
    std::array<int,4> perm{};
    for (int i = 0; i < 4; ++i) {
      int cubie = cornerCubieAt(s, slotOrder[i]);
      int which = invMap[cubie];
      assert(which >= 0 && which < 4 && "corner hors tétrade (non-G4 ?)");
      perm[i] = which;
    }
    return perm;
  };
  auto permEdges = [&](const std::array<int,4>& slotOrder,
                       const std::array<int,12>& invMap) {
    std::array<int,4> perm{};
    for (int i = 0; i < 4; ++i) {
      int cubie = edgeCubieAt(s, slotOrder[i]);
      int which = invMap[cubie];
      assert(which >= 0 && which < 4 && "edge hors tétrade (non-G4 ?)");
      perm[i] = which;
    }
    return perm;
  };

  uint8_t cU = rankS4(permCorners(U_CORNER_SLOTS, INV_UC));
  uint8_t cD = rankS4(permCorners(D_CORNER_SLOTS, INV_DC));
  uint8_t eU = rankS4(permEdges  (U_EDGE_SLOTS,   INV_UE));
  uint8_t eM = rankS4(permEdges  (M_EDGE_SLOTS,   INV_ME));
  uint8_t eD = rankS4(permEdges  (D_EDGE_SLOTS,   INV_DE));

  return G4Key{ cU, cD, eU, eM, eD };
}

inline uint32_t keyToRaw(const G4Key& k) {
  return (((((uint32_t)k.cU)*24 + k.cD)*24 + k.eU)*24 + k.eM)*24 + k.eD;
}

// === Tables de mapping ===
static std::vector<int32_t>  map24toCompact(24*24*24*24*24, -1); // ~8.0M
static std::vector<uint32_t> compactToRaw;                       // 663,552

static constexpr SpinLst G4_MOVES[6] = { U2, D2, L2, R2, F2, B2 };

// buildG4Indexing générique : on te laisse brancher ta fonction d’application de move.
template <class ApplyMove>
void buildG4Indexing(ApplyMove applyMove) {
  if (!compactToRaw.empty()) return; // déjà construit
  compactToRaw.reserve(663552);

  std::queue<CubeState> q;
  std::unordered_set<CubeState, CubeStateHash> seen;

  CubeState solved{}; // par défaut: état résolu (edges/corners init aux constantes solved)
  q.push(solved);
  seen.insert(solved);

  while (!q.empty()) {
    CubeState s = q.front(); q.pop();

    G4Key k = extractG4Key(s);
    uint32_t raw = keyToRaw(k);

    int32_t idx = map24toCompact[raw];
    if (idx == -1) {
      idx = (int32_t)compactToRaw.size();
      map24toCompact[raw] = idx;
      compactToRaw.push_back(raw);
    }

    for (SpinLst m : G4_MOVES) {
      CubeState t = s;
      applyMove(t, m);                 // <- branché sur ton spinManager.applyMove
      if (seen.insert(t).second) q.push(t);
    }
  }

  assert(compactToRaw.size() == 663552 && "Le BFS G4 doit couvrir 663,552 états");
}

uint32_t encodeG4(const CubeState& state) {
  G4Key k = extractG4Key(state);
  uint32_t raw = keyToRaw(k);
  return map24toCompact[raw]; // -1 si non atteint (ne devrait pas en phase 4)
}