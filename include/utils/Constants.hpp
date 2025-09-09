#pragma once

// uint64_t encodeEdges() {
//     uint64_t edges = 0;
//     for (int i = 0; i < 12; ++i) {
//         edges |= (static_cast<uint64_t>(i) & 0xF) << (4 * i);
//     }
//     return edges;
// }
#define EDGES_SOLVED_STATE      0xBA9876543210ULL


// uint64_t encodeCorners() {
//     uint64_t corners = 0;
//     for (int i = 0; i < 8; ++i) {
//         corners |= (static_cast<uint64_t>(i) & 0xF) << (i * 4);
//     }
//     return corners;
// }
#define CORNERS_SOLVED_STATE    0x76543210ULL

#define SPIN_COUNT 18

enum CornersPieceLst {
    URF, // 0
    UFL, // 1
    ULB, // 2
    UBR, // 3
    DFR, // 4
    DLF, // 5
    DBL, // 6
    DRB  // 7
};

enum EdgesPieceLst {
    UR, // 0
    UF, // 1
    UL, // 2
    UB, // 3
    DR, // 4
    DF, // 5
    DL, // 6
    DB, // 7
    FR, // 8
    FL, // 9
    BL, // 10
    BR, // 11
};

enum Color {
    e_YELLOW, // face Up
    e_BLUE, // face Left
    e_RED, // face Front
    e_GREEN, // face Right
    e_ORANGE, // face Back
    e_WHITE // face Down
};

#define ALGO_MODE 1

#define cornersOrientation 2187 // 3^7
#define edgesOrientation 2048 // 2^11
#define sliceEdgesOrientation 495 // 9C4