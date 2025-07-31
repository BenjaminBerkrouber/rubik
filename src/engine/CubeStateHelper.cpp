#include "../include/engine/CubeStateHelper.hpp"
#include <iostream>
#include <iomanip>

CubeStateHelper::CubeStateHelper(CubeState &cube)
    : _cube(cube),
        _corners{
            CornersPiece({{Color::e_YELLOW, Color::e_GREEN, Color::e_RED}}, CornersPieceLst::URF),
            CornersPiece({{Color::e_YELLOW, Color::e_RED, Color::e_BLUE}}, CornersPieceLst::UFL),
            CornersPiece({{Color::e_YELLOW, Color::e_BLUE, Color::e_ORANGE}}, CornersPieceLst::ULB),
            CornersPiece({{Color::e_YELLOW, Color::e_ORANGE, Color::e_GREEN}}, CornersPieceLst::UBR),
            CornersPiece({{Color::e_WHITE, Color::e_RED, Color::e_GREEN}}, CornersPieceLst::DFR),
            CornersPiece({{Color::e_WHITE, Color::e_BLUE, Color::e_RED}}, CornersPieceLst::DLF),
            CornersPiece({{Color::e_WHITE, Color::e_ORANGE, Color::e_BLUE}}, CornersPieceLst::DBL),
            CornersPiece({{Color::e_WHITE, Color::e_GREEN, Color::e_ORANGE}}, CornersPieceLst::DRB)
        },
        _edges{
            EdgesPiece({{Color::e_YELLOW, Color::e_GREEN}}, EdgesPieceLst::UR),
            EdgesPiece({{Color::e_YELLOW, Color::e_RED}}, EdgesPieceLst::UF),
            EdgesPiece({{Color::e_YELLOW, Color::e_BLUE}}, EdgesPieceLst::UL),
            EdgesPiece({{Color::e_YELLOW, Color::e_ORANGE}}, EdgesPieceLst::UB),
            EdgesPiece({{Color::e_WHITE, Color::e_GREEN}}, EdgesPieceLst::DR),
            EdgesPiece({{Color::e_WHITE, Color::e_RED}}, EdgesPieceLst::DF),
            EdgesPiece({{Color::e_WHITE, Color::e_BLUE}}, EdgesPieceLst::DL),
            EdgesPiece({{Color::e_WHITE, Color::e_ORANGE}}, EdgesPieceLst::DB),
            EdgesPiece({{Color::e_RED, Color::e_GREEN}}, EdgesPieceLst::FR),
            EdgesPiece({{Color::e_RED, Color::e_BLUE}}, EdgesPieceLst::FL),
            EdgesPiece({{Color::e_ORANGE, Color::e_BLUE}}, EdgesPieceLst::BL),
            EdgesPiece({{Color::e_ORANGE, Color::e_GREEN}}, EdgesPieceLst::BR)
        }
{}

CubeStateHelper::~CubeStateHelper() = default;



void printEdgesBinary(uint64_t edges) {
    constexpr int totalNibbles = 12;

    std::cout << "Edge:                ";
    for (int i = 0; i < totalNibbles; ++i) {
        uint8_t nibble = (edges >> (i * 4)) & 0xF;
        std::cout << std::right << static_cast<unsigned int>(nibble)
                << " ";
    }

    std::cout << std::endl << "Edge Orientation:    ";
    for (int i = 48; i < 60; ++i) {
        std::cout << std::right << ((edges >> i) & 0x1)
                << " ";
    }
    std::cout << std::endl;
}

void printCornersBinary(uint64_t corners) {
    constexpr int totalCorners = 8;

    std::cout << "Corners:             ";
    for (int i = 0; i < totalCorners; ++i) {
        uint8_t corner = (corners >> (i * 4)) & 0xF;
        std::cout << std::right << static_cast<unsigned int>(corner) << " ";
    }

    std::cout << std::endl << "Corners Orientation: ";
    for (int i = 0; i < totalCorners; ++i) {
        uint8_t orientation = (corners >> (32 + i * 2)) & 0x3;
        std::cout << std::right << static_cast<unsigned int>(orientation) << " ";
    }

    std::cout << std::endl;
}


void CubeStateHelper::printState() const {
    std::cout << "___ Cube State: ___" << std::endl;
    printCornersBinary(_cube.corners);
    printEdgesBinary(_cube.edges);
    std::cout << "____________________" << std::endl;
}

int getPieceAtIndex(uint64_t pieces, int i) {
    uint8_t piece = (pieces >> (i * 4)) & 0xF;
    return piece;
}

int getPieceCornerOrientation(uint64_t pieces, int i) {
    uint8_t orientation = (pieces >> (32 + i * 2)) & 0x3;
    return orientation;
}
int getPieceEdgeOrientation(uint64_t pieces, int i) {
    uint8_t orientation = ((pieces >> (48 + i)) & 0x1);
    return orientation;
}

std::string getColor(int i, std::string name) {
    std::string color;
    switch (i) {
        case Color::e_YELLOW: color = YELLOW; break;
        case Color::e_BLUE: color = BLUE; break;
        case Color::e_RED: color = RED; break;
        case Color::e_GREEN: color = GREEN; break;
        case Color::e_ORANGE: color = ORANGE; break;
        case Color::e_WHITE: color = WHITE; break;
    }
    color += name.substr(0, 5) + std::string(5 - std::min<size_t>(name.length(), 5), ' ');
    color += RESET;
    return color;
}

std::string CubeStateHelper::getCcolor(int i, int o) const {
    int index = getPieceAtIndex(_cube.corners, i);
    int orientation = getPieceCornerOrientation(_cube.corners, i);
    CornersPiece corner = _corners[index];
    int colorId = corner.getColor((o + orientation) % 3);
    return getColor(colorId, corner.getName() + "." + std::to_string((o + orientation) % 3)) + "  ";
}

std::string CubeStateHelper::getEColor(int i, int o) const {
    int index = getPieceAtIndex(_cube.edges, i);
    int orientation = getPieceEdgeOrientation(_cube.edges, i);
    EdgesPiece edge = _edges[index];
    int colorId = edge.getColor((o + orientation) % 2);
    return getColor(colorId, edge.getName() + "." + std::to_string((o + orientation) % 2)) + "  ";
}

std::string CubeStateHelper::getCenter(int i) const {
    switch (i) {
        case Color::e_YELLOW: return std::string(YELLOW) + "  U  " + RESET + "  ";
        case Color::e_BLUE: return std::string(BLUE) + "  L  " + RESET + "  ";
        case Color::e_RED: return std::string(RED) + "  F  " + RESET + "  ";
        case Color::e_GREEN: return std::string(GREEN) + "  R  " + RESET + "  ";
        case Color::e_ORANGE: return std::string(ORANGE) + "  B  " + RESET + "  ";
        case Color::e_WHITE: return std::string(WHITE) + "  D  " + RESET + "  ";
        default: return std::string(RESET) + "     ";
    }
}

void CubeStateHelper::printFace(const std::pair<uint8_t, uint8_t> _face[9], int faceName, std::string padding) const {
    std::cout << padding << getCcolor(_face[0].first, _face[0].second) << getEColor(_face[1].first, _face[1].second) << getCcolor(_face[2].first, _face[2].second) << std::endl << std::endl;
    std::cout << padding << getEColor(_face[3].first, _face[3].second) << getCenter(faceName) << getEColor(_face[5].first, _face[5].second) << std::endl << std::endl;
    std::cout << padding << getCcolor(_face[6].first, _face[6].second) << getEColor(_face[7].first, _face[7].second) << getCcolor(_face[8].first, _uP[8].second) << std::endl << std::endl;
    std::cout << std::endl;
}


void CubeStateHelper::print() const {
    std::string padding = "                       ";
    std::string smallSpace = "  ";

    printState();

    printFace(_uP, e_YELLOW, padding);

    std::cout << getCcolor(_lP[0].first, _lP[0].second) << getEColor(_lP[1].first, _lP[1].second) << getCcolor(_lP[2].first, _lP[2].second) << smallSpace
        << getCcolor(_fP[0].first, _fP[0].second) << getEColor(_fP[1].first, _fP[1].second) << getCcolor(_fP[2].first, _fP[2].second) << smallSpace
        << getCcolor(_rP[0].first, _rP[0].second) << getEColor(_rP[1].first, _rP[1].second) << getCcolor(_rP[2].first, _rP[2].second) << smallSpace
        << getCcolor(_bP[0].first, _bP[0].second) << getEColor(_bP[1].first, _bP[1].second) << getCcolor(_bP[2].first, _bP[2].second) << std::endl << std::endl;

    std::cout << getEColor(_lP[3].first, _lP[3].second) << BLUE << getCenter(e_BLUE) << getEColor(_lP[5].first, _lP[5].second) << smallSpace
        << getEColor(_fP[3].first, _fP[3].second) << getCenter(e_RED) << getEColor(_fP[5].first, _fP[5].second) << smallSpace
        << getEColor(_rP[3].first, _rP[3].second) << getCenter(e_GREEN) << getEColor(_rP[5].first, _rP[5].second) << smallSpace
        << getEColor(_bP[3].first, _bP[3].second) << getCenter(e_ORANGE) << getEColor(_bP[5].first, _bP[5].second) << std::endl << std::endl;

    std::cout << getCcolor(_lP[6].first, _lP[6].second) << getEColor(_lP[7].first, _lP[7].second) << getCcolor(_lP[8].first, _lP[8].second) << smallSpace
        << getCcolor(_fP[6].first, _fP[6].second) << getEColor(_fP[7].first, _fP[7].second) << getCcolor(_fP[8].first, _fP[8].second) << smallSpace
        << getCcolor(_rP[6].first, _rP[6].second) << getEColor(_rP[7].first, _rP[7].second) << getCcolor(_rP[8].first, _rP[8].second) << smallSpace
        << getCcolor(_bP[6].first, _bP[6].second) << getEColor(_bP[7].first, _bP[7].second) << getCcolor(_bP[8].first, _bP[8].second) << std::endl << std::endl;;

    printFace(_dP, e_WHITE, padding);
    std::cout << std::endl;
}