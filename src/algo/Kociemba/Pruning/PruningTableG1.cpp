#include "../../../../include/algo/Kociemba/Pruning/PruningTableG1.hpp"

/* ===========================================================================
==== Constructor and Destructor
=========================================================================== */


PruningTableG1::PruningTableG1() {
    corners_orientation_pruning_table.fill(0xFF);
    edges_orientation_pruning_table.fill(0xFF);
    edges_slice_pruning_table.fill(0xFF);
    init_nCrTable();
    generateTable();
}

PruningTableG1::~PruningTableG1() = default;




/* ===========================================================================
==== Pruning Table Generation
=========================================================================== */


void PruningTableG1::generateTable() {
    corners_orientation_pruning_table = generateCornersOrientationPruningTable();
    edges_orientation_pruning_table = generateEdgesOrientationPruningTable();
    edges_slice_pruning_table = generateEdgesSlicePruningTable();
}

std::array<uint8_t, 2187> PruningTableG1::generateCornersOrientationPruningTable() {
    std::array<uint8_t, 2187> table;
    table.fill(0xFF);

    std::queue<std::pair<Cube, uint8_t>> q;

    Cube solved;
    int start_index = encodeCornersOrientation(solved.getCornerOrientations());
    table[start_index] = 0;

    q.push({solved, 0});

    while (!q.empty()) {
        auto [cube, depth] = q.front(); q.pop();

        for (SpinId move : allowedSpins_) {
            Cube next = cube;
            next.applySpin(move);

            int index = encodeCornersOrientation(next.getCornerOrientations());
            if (table[index] == 0xFF) {
                table[index] = depth + 1;
                q.push({next, depth + 1});
            }
        }
    }
    // std::cout << "Corners orientation pruning table generated." << std::endl;
    // std::cout << "Table size: " << table.size() << " bytes." << std::endl;
    return table;
}


std::array<uint8_t, 4096> PruningTableG1::generateEdgesOrientationPruningTable() {
    std::array<uint8_t, 4096> table;
    table.fill(0xFF);

    std::queue<std::pair<Cube, uint8_t>> q;

    Cube solved;
    int start_index = encodeEgdeOrientation(solved.getEdgeOrientations());
    table[start_index] = 0;

    q.push({solved, 0});

    while (!q.empty()) {
        auto [cube, depth] = q.front(); q.pop();

        for (SpinId move : allowedSpins_) {
            Cube next = cube;
            next.applySpin(move);

            int index = encodeEgdeOrientation(next.getEdgeOrientations());
            if (table[index] == 0xFF) {
                table[index] = depth + 1;
                q.push({next, depth + 1});
            }
        }
    }
    // std::cout << "Edges orientation pruning table generated." << std::endl;
    // std::cout << "Table size: " << table.size() << " bytes." << std::endl;
    return table;
}


std::array<uint8_t, 494> PruningTableG1::generateEdgesSlicePruningTable() {
    std::array<uint8_t, 494> table;
    table.fill(0xFF);

    std::queue<std::pair<Cube, uint8_t>> q;

    Cube solved;
    int start_index = encodeEdgesSlice(solved.getEdges());
    table[start_index] = 0;

    q.push({solved, 0});

    while (!q.empty()) {
        auto [cube, depth] = q.front(); q.pop();

        for (SpinId move : allowedSpins_) {
            Cube next = cube;
            next.applySpin(move);

            int index = encodeEdgesSlice(next.getEdges());
            if (table[index] == 0xFF) {  // non visité
                table[index] = depth + 1; // marquer avant push !
                q.push({next, depth + 1});
            }
        }
    }

    return table;
}







/* ===========================================================================
==== Encoding Functions
=========================================================================== */

int PruningTableG1::encodeCornersOrientation(const std::array<uint8_t, 8>& corners_orientation) {
    int index = 0;
    for (int i = 0; i < 7; ++i) {
        index = index * 3 + corners_orientation[i];
    }
    return index;
}

int PruningTableG1::encodeEgdeOrientation(const std::array<uint8_t, 12>& edges_orientation) {
    int index = 0;
    for (int i = 0; i < 11; ++i) {
        index = (index << 1) | (edges_orientation[i] & 1);
    }
    return index;
}


int PruningTableG1::nCrTable[PruningTableG1::MAX_N + 1][PruningTableG1::MAX_R + 1] = {};


void PruningTableG1::init_nCrTable() {
    for (int n = 0; n <= MAX_N; ++n) {
        nCrTable[n][0] = 1;
        for (int r = 1; r <= std::min(n, MAX_R); ++r) {
            if (r == n) {
                nCrTable[n][r] = 1;
            } else {
                nCrTable[n][r] = nCrTable[n - 1][r - 1] + nCrTable[n - 1][r];
            }
        }
    }
}

int PruningTableG1::nCr(int n, int r) {
    return nCrTable[n][r];
}

bool isUDSliceEdge(uint8_t edge) {
    return edge >= 4 && edge <= 7; // FR, FL, BL, BR
}

int PruningTableG1::encodeEdgesSlice(const std::array<uint8_t, 12>& edges) {
    int index = 0;
    int r = 4;

    for (int i = 0; i < 12; ++i) {
        if (isUDSliceEdge(edges[i])) {
            --r;
        } else {
            index += nCr(12 - 1 - i, r);
        }
    }

    return index;
}






int PruningTableG1::encodeCube(const Cube& cube) const {
    int corners_orientation_index = encodeCornersOrientation(cube.getCornerOrientations());
    int edges_orientation_index = encodeEgdeOrientation(cube.getEdgeOrientations());
    int edges_slice_index = encodeEdgesSlice(cube.getEdges());

    return (corners_orientation_index * 4096) + (edges_orientation_index * 494) + edges_slice_index;
}


/* ===========================================================================
==== Decoding Functions
=========================================================================== */


std::array<uint8_t, 8> PruningTableG1::decodeCornerOrientation(int index) {
    std::array<uint8_t, 8> corner_orientations{};
    int sum = 0;

    for (int i = 6; i >= 0; --i) {
        corner_orientations[i] = index % 3;
        sum += corner_orientations[i];
        index /= 3;
    }

    corner_orientations[7] = (3 - (sum % 3)) % 3;

    return corner_orientations;
}

std::array<uint8_t, 12> PruningTableG1::decodeEdgeOrientation(int index) {
    std::array<uint8_t, 12> edge_orientations{};
    int sum = 0;

    for (int i = 10; i >= 0; --i) {
        edge_orientations[i] = index & 1;
        sum += edge_orientations[i];
        index >>= 1;
    }
    edge_orientations[11] = (2 - (sum % 2)) % 2;
    return edge_orientations;
}

std::array<uint8_t, 12> PruningTableG1::decodeEdgesSlice(int slice_index) {
    std::array<uint8_t, 12> edges{};
    int r = 4;

    for (int i = 11; i >= 0; --i) {
        if (slice_index >= nCr(i, r) && r > 0) {
            slice_index -= nCr(i, r);
            edges[i] = 1;
            --r;
        } else {
            edges[i] = 0;
        }
    }

    uint8_t slice_val = 4;
    uint8_t nonslice_val = 0;
    for (int i = 0; i < 12; ++i) {
        if (edges[i]) {
            edges[i] = slice_val++;
        } else {
        
            while (nonslice_val >= 4 && nonslice_val <= 7) ++nonslice_val;
            edges[i] = nonslice_val++;
        }
    }

    return edges;
}



const Cube &PruningTableG1::decodeCube(int index) const {
    static Cube cube;
    
    int corners_orientation_index = index / 4096;
    int edges_orientation_index = (index % 4096) / 494;
    int edges_slice_index = index % 494;

    cube.setCornerOrientations(decodeCornerOrientation(corners_orientation_index));
    cube.setEdgeOrientations(decodeEdgeOrientation(edges_orientation_index));
    cube.setEdges(decodeEdgesSlice(edges_slice_index));

    return cube;
}


/* ===========================================================================
==== Getters
=========================================================================== */

const std::array<uint8_t, 2187>& PruningTableG1::getCornersOrientationPruningTable() const {
    return corners_orientation_pruning_table;
}

const std::array<uint8_t, 4096>& PruningTableG1::getEdgesOrientationPruningTable() const {
    return edges_orientation_pruning_table;
}

const std::array<uint8_t, 494>& PruningTableG1::getEdgesSlicePruningTable() const {
    return edges_slice_pruning_table;
}