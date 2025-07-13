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