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

    initializeMapping();
}

Cube::~Cube() {}


// ============================================================================
// ==== Init
// ============================================================================

void Cube::initializeMapping() {
    mapping_corners[0] = {YELLOW, GREEN, RED};      // UFR
    mapping_corners[1] = {YELLOW, RED, BLUE};       // UFL
    mapping_corners[2] = {YELLOW, BLUE, ORANGE};    // UBL
    mapping_corners[3] = {YELLOW, ORANGE, GREEN};   // UBR

    mapping_corners[4] = {WHITE, RED, GREEN};       // DFR
    mapping_corners[5] = {WHITE, BLUE, RED};        // DFL
    mapping_corners[6] = {WHITE, ORANGE, BLUE};     // DBL 
    mapping_corners[7] = {WHITE, GREEN, ORANGE};    // DBR

    mapping_edges[0] = {YELLOW, RED};               // UF
    mapping_edges[1] = {YELLOW, BLUE};              // UL
    mapping_edges[2] = {YELLOW, ORANGE};            // UB
    mapping_edges[3] = {YELLOW, GREEN};             // UR

    mapping_edges[4] = {RED, GREEN};                // FR
    mapping_edges[5] = {RED, BLUE};                 // FL
    mapping_edges[6] = {ORANGE, BLUE};              // BL
    mapping_edges[7] = {ORANGE, GREEN};             // BR

    mapping_edges[8] = {WHITE, RED};                // DF
    mapping_edges[9] = {WHITE, BLUE};               // DL
    mapping_edges[10] = {WHITE, ORANGE};            // DB
    mapping_edges[11] = {WHITE, GREEN};             // DR
}




// ============================================================================
// ==== Methods
// ============================================================================


void Cube::applySpin(const std::string& spinName) {
    const Spin& spin = SpinLib::getInstance().getSpin(spinName);

    std::cout << "  Applying spin: " << spinName << std::endl;

    std::vector<uint8_t> tmpCorners(std::begin(corners), std::end(corners));
    std::vector<uint8_t> tmpEdges(std::begin(edges), std::end(edges));
    std::vector<uint8_t> tmpCornersOrientation(std::begin(corners_orientation), std::end(corners_orientation));
    std::vector<uint8_t> tmpEdgesOrientation(std::begin(edges_orientation), std::end(edges_orientation));


    for (const auto& move : spin.cornersMoves) {
        corners[move.to] = tmpCorners[move.from];
        corners_orientation[move.to] = (tmpCornersOrientation[move.from] + getCornerOrientationDelta(spin, move.to)) % 3;
    }

    for (const auto& move : spin.edgesMoves) {
        edges[move.to] = tmpEdges[move.from];
        edges_orientation[move.to] = (tmpEdgesOrientation[move.from] + getEdgeOrientationDelta(spin, move.to)) % 2;
    }
}




// ============================================================================
// ==== Getters
// ============================================================================


int Cube::getCornerOrientationDelta(const Spin& spin, uint8_t index) {
    for (const auto& oc : spin.cornersOrientation) {
        if (oc.index == index) return oc.delta;
    }
    return 0;
}

int Cube::getEdgeOrientationDelta(const Spin& spin, uint8_t index) {
    for (const auto& oc : spin.edgesOrientation) {
        if (oc.index == index) return oc.delta;
    }
    return 0;
}


std::string Cube::getCorners() const {

    std::string result;
    for (uint8_t i = 0; i < 8; ++i) {
        result += std::to_string(corners[i]);
        result += " ";
    }
    return result;
}

std::string Cube::getCornerOrientations() const {
    std::string result;
    for (uint8_t i = 0; i < 8; ++i) {
        result += std::to_string(corners_orientation[i]);
        result += " ";
    }
    return result;
} 


std::string Cube::getEdges() const {
    std::string result;
    for (uint8_t i = 0; i < 12; ++i) {
        result += std::to_string(edges[i]);
        result += " ";
    }
    return result;
}

std::string Cube::getEdgeOrientations() const {
    std::string result;
    for (uint8_t i = 0; i < 12; ++i) {
        result += std::to_string(edges_orientation[i]);
        result += " ";
    }
    return result;
}

// ============================================================================
// ==== Print
// ============================================================================


std::string Cube::getCornerSticker(uint8_t cornerIndex, uint8_t cornerFaceIndex) const {
    if (cornerIndex >= 8) throw std::out_of_range("Invalid corner index");
    if (cornerFaceIndex >= 3) throw std::out_of_range("Invalid corner orientation");

    uint8_t corner = corners[cornerIndex];
    uint8_t cornerOrientation = corners_orientation[cornerIndex];

    return mapping_corners.at(corner).at((cornerFaceIndex + cornerOrientation) % 3) + " C " + RESET;
}

std::string Cube::getEdgeSticker(uint8_t edgeIndex, uint8_t edgeFaceIndex) const {
    if (edgeIndex >= 12) throw std::out_of_range("Invalid edge index");
    if (edgeFaceIndex >= 2) throw std::out_of_range("Invalid edge orientation");

    uint8_t edge = edges[edgeIndex];
    uint8_t edgeOrientation = edges_orientation[edgeIndex];

    return mapping_edges.at(edge).at((edgeFaceIndex + edgeOrientation) % 2) + " E " + RESET;
}



std::string Cube::getLine(std::pair<uint8_t, uint8_t>& left, std::pair<uint8_t, uint8_t>& center, std::pair<uint8_t, uint8_t>& right) {
    return getCornerSticker(left.first, left.second) + " " 
        + getEdgeSticker(center.first, center.second) + " " 
        + getCornerSticker(right.first, right.second);
}

std::string Cube::getMiddleLine(std::pair<uint8_t, uint8_t>& left, const std::string& color, std::pair<uint8_t, uint8_t>& right) {
    return getEdgeSticker(left.first, left.second) + " " 
        + color + " M " + RESET + " " 
        + getEdgeSticker(right.first, right.second);
}


void Cube::print() {

    std::string spaces(14, ' ');
    std::cout   << spaces << getLine(uP[0], uP[1], uP[2]) << std::endl 
                << spaces << getMiddleLine(uP[3], YELLOW, uP[5]) << std::endl 
                << spaces << getLine(uP[6], uP[7], uP[8]) << std::endl << std::endl;

    std::cout << getLine(lP[0], lP[1], lP[2]) 
                << "   " << getLine(fP[0], fP[1], fP[2])
                << "   " << getLine(rP[0], rP[1], rP[2])
                << "   " << getLine(bP[0], bP[1], bP[2]) << std::endl;

    std::cout << getMiddleLine(lP[3], BLUE, lP[5]) 
                << "   " << getMiddleLine(fP[3], RED, fP[5])
                << "   " << getMiddleLine(rP[3], GREEN, rP[5])
                << "   " << getMiddleLine(bP[3], ORANGE, bP[5]) << std::endl;


    std::cout << getLine(lP[6], lP[7], lP[8]) 
            << "   " << getLine(fP[6], fP[7], fP[8])
            << "   " << getLine(rP[6], rP[7], rP[8])
            << "   " << getLine(bP[6], bP[7], bP[8]) << std::endl << std::endl;

    std::cout   << spaces << getLine(dP[0], dP[1], dP[2]) << std::endl
                << spaces << getMiddleLine(dP[3], WHITE, dP[5]) << std::endl
                << spaces << getLine(dP[6], dP[7], dP[8])  << std::endl;
}

