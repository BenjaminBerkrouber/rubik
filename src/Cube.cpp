#include "../include/Cube.hpp"

// ================================================================================
// ==== Constructor and Destructor 
// ================================================================================


Cube::Cube() {
    for (uint8_t i = 0; i < 8; ++i) {
        corners[i] = i;
        corners_orientation[i] = 0;
    }
    for (uint8_t i = 0; i < 12; ++i) {
        edges[i] = i;
        edges_orientation[i] = 0;
    }
}

Cube::~Cube() {}


// ============================================================================
// ==== Methods
// ============================================================================


void Cube::applySimpleMove(auto &dest, auto &dest_orientation, const auto& moves, int mod) {
    auto lastVal = dest[moves.back().index];
    auto lastOri = dest_orientation[moves.back().index];

    for (int i = moves.size() - 1; i > 0; --i) {
        dest[moves[i].index] = dest[moves[i - 1].index];
        dest_orientation[moves[i].index] = (dest_orientation[moves[i - 1].index] + moves[i - 1].delta) % mod;
    }

    dest[moves[0].index] = lastVal;
    dest_orientation[moves[0].index] = (lastOri + moves.back().delta) % mod;
}

void Cube::applyDoubleMove(auto& dest, auto &dest_orientation, const auto& moves, int mod) {

    std::swap(dest[moves[0].index], dest[moves[1].index]);
    std::swap(dest[moves[2].index], dest[moves[3].index]);

    dest_orientation[moves[0].index] = (dest_orientation[moves[0].index] + moves[0].delta) % mod;
    dest_orientation[moves[1].index] = (dest_orientation[moves[1].index] + moves[1].delta) % mod;
    dest_orientation[moves[2].index] = (dest_orientation[moves[2].index] + moves[2].delta) % mod;
    dest_orientation[moves[3].index] = (dest_orientation[moves[3].index] + moves[3].delta) % mod;
}


void Cube::applySpin(SpinId id) {
    const Spin& spin = spinLib.getSpin(id);
    
    if (id < SpinId::U2) {
        applySimpleMove(corners, corners_orientation, spin.cornersMoves, 3);
        applySimpleMove(edges, edges_orientation, spin.edgesMoves, 2);
    } else {
        applyDoubleMove(corners, corners_orientation, spin.cornersMoves, 3);
        applyDoubleMove(edges, edges_orientation, spin.edgesMoves, 3);
    }
}


// ============================================================================
// ==== Getters
// ============================================================================


const std::array<uint8_t, 8> &Cube::getCorners() const {
    return corners;
}

const std::array<uint8_t, 8> &Cube::getCornerOrientations() const {
    return corners_orientation;
}

const std::array<uint8_t, 12> &Cube::getEdges() const {
    return edges;
}

const std::array<uint8_t, 12> &Cube::getEdgeOrientations() const {
    return edges_orientation;
}

// ============================================================================
// ==== Setters
// ============================================================================

void Cube::setCorners(const std::array<uint8_t, 8>& new_corners) {
    corners = new_corners;
}

void Cube::setCornerOrientations(const std::array<uint8_t, 8>& new_corners_orientation) {
    corners_orientation = new_corners_orientation;
}

void Cube::setEdges(const std::array<uint8_t, 12>& new_edges) {
    edges = new_edges;
}

void Cube::setEdgeOrientations(const std::array<uint8_t, 12>& new_edges_orientation) {
    edges_orientation = new_edges_orientation;
}