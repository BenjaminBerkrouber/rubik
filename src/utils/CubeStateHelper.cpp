#include "../include/utils/CubeStateHelper.hpp"
#include <iostream>
#include <iomanip>

CubeStateHelper::CubeStateHelper(const CubeState &cube)
    : _cube(cube),
        _corners{
            CornersPiece({{Color::e_YELLOW, Color::e_RED, Color::e_GREEN}}, CornersPieceLst::URF),
            CornersPiece({{Color::e_YELLOW, Color::e_BLUE, Color::e_RED}}, CornersPieceLst::UFL),
            CornersPiece({{Color::e_YELLOW, Color::e_ORANGE, Color::e_BLUE}}, CornersPieceLst::ULB),
            CornersPiece({{Color::e_YELLOW, Color::e_GREEN, Color::e_ORANGE}}, CornersPieceLst::UBR),
            CornersPiece({{Color::e_WHITE, Color::e_GREEN, Color::e_RED}}, CornersPieceLst::DFR),
            CornersPiece({{Color::e_WHITE, Color::e_RED, Color::e_BLUE}}, CornersPieceLst::DLF),
            CornersPiece({{Color::e_WHITE, Color::e_BLUE, Color::e_ORANGE}}, CornersPieceLst::DBL),
            CornersPiece({{Color::e_WHITE, Color::e_ORANGE, Color::e_GREEN}}, CornersPieceLst::DRB)
        },
        _edges{
            EdgesPiece({{Color::e_YELLOW, Color::e_RED}}, EdgesPieceLst::UR),
            EdgesPiece({{Color::e_YELLOW, Color::e_BLUE}}, EdgesPieceLst::UF),
            EdgesPiece({{Color::e_YELLOW, Color::e_ORANGE}}, EdgesPieceLst::UL),
            EdgesPiece({{Color::e_YELLOW, Color::e_GREEN}}, EdgesPieceLst::UB),
            EdgesPiece({{Color::e_RED, Color::e_GREEN}}, EdgesPieceLst::DR),
            EdgesPiece({{Color::e_RED, Color::e_BLUE}}, EdgesPieceLst::DF),
            EdgesPiece({{Color::e_ORANGE, Color::e_BLUE}}, EdgesPieceLst::DL),
            EdgesPiece({{Color::e_ORANGE, Color::e_GREEN}}, EdgesPieceLst::DB),
            EdgesPiece({{Color::e_WHITE, Color::e_RED}}, EdgesPieceLst::FR),
            EdgesPiece({{Color::e_WHITE, Color::e_BLUE}}, EdgesPieceLst::FL),
            EdgesPiece({{Color::e_WHITE, Color::e_ORANGE}}, EdgesPieceLst::BL),
            EdgesPiece({{Color::e_WHITE, Color::e_GREEN}}, EdgesPieceLst::BR)
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


void CubeStateHelper::printState() {
    printCornersBinary(_cube.corners);
    printEdgesBinary(_cube.edges);
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
    uint8_t orientation = ((pieces >> i) & 0x1);
    return orientation;
}

std::string getColor(int i) {
    std::string color;
    switch (i) {
        case Color::e_YELLOW: color = YELLOW; break;
        case Color::e_BLUE: color = BLUE; break;
        case Color::e_RED: color = RED; break;
        case Color::e_GREEN: color = GREEN; break;
        case Color::e_ORANGE: color = ORANGE; break;
        case Color::e_WHITE: color = WHITE; break;
    }
    color += "  ";
    color += RESET;
    return color;
}

std::string CubeStateHelper::getCornerSticker(int i, int o) {
    int index = getPieceAtIndex(_cube.corners, i);
    int orientation = getPieceCornerOrientation(_cube.corners, o);
    int colorId = _corners[index].getColor(o + orientation);
    return getColor(colorId) + "  ";
}

std::string CubeStateHelper::getEdgeSticker(int i, int o) {
    int index = getPieceAtIndex(_cube.corners, i);
    int orientation = getPieceEdgeOrientation(_cube.corners, o);
    int colorId = _corners[index].getColor(o + orientation);
    return getColor(colorId) + "  ";
}

void CubeStateHelper::printCube() {

    std::string space = "              ";
    std::string smallSpace = "  ";

    std::cout << space << getCornerSticker(_uP[0].first, _uP[0].second) << getEdgeSticker(_uP[1].first, _uP[1].second) << getCornerSticker(_uP[2].first, _uP[2].second) << std::endl << std::endl;
    std::cout << space << getCornerSticker(_uP[3].first, _uP[3].second) << YELLOW << "  " << RESET << "  " << getCornerSticker(_uP[5].first, _uP[5].second) << std::endl << std::endl;
    std::cout << space << getCornerSticker(_uP[6].first, _uP[6].second) << getEdgeSticker(_uP[7].first, _uP[7].second) << getCornerSticker(_uP[8].first, _uP[8].second) << std::endl << std::endl;

    std::cout << getCornerSticker(_lP[0].first, _lP[0].second) << getEdgeSticker(_lP[1].first, _lP[1].second) << getCornerSticker(_lP[8].first, _lP[8].second) << smallSpace
        << getCornerSticker(_fP[0].first, _fP[0].second) << getEdgeSticker(_fP[1].first, _fP[1].second) << getCornerSticker(_fP[3].first, _fP[3].second) << smallSpace
        << getCornerSticker(_rP[0].first, _rP[0].second) << getEdgeSticker(_rP[1].first, _rP[1].second) << getCornerSticker(_rP[3].first, _rP[3].second) << smallSpace
        << getCornerSticker(_bP[0].first, _bP[0].second) << getEdgeSticker(_bP[1].first, _bP[1].second) << getCornerSticker(_bP[3].first, _bP[3].second) << std::endl << std::endl;

    std::cout << getEdgeSticker(_lP[0].first, _lP[0].second) << BLUE << "  " << RESET << "  " << getEdgeSticker(_lP[8].first, _lP[8].second) << smallSpace
        << getEdgeSticker(_fP[0].first, _fP[0].second) <<  RED << "  " << RESET << "  " << getEdgeSticker(_fP[8].first, _fP[8].second) << smallSpace
        << getEdgeSticker(_rP[0].first, _rP[0].second) << GREEN << "  " << RESET << "  " << getEdgeSticker(_rP[8].first, _rP[8].second) << smallSpace
        << getEdgeSticker(_bP[0].first, _bP[0].second) << ORANGE << "  " << RESET << "  " << getEdgeSticker(_bP[8].first, _bP[8].second) << std::endl << std::endl;

    std::cout << getCornerSticker(_lP[6].first, _lP[6].second) << getEdgeSticker(_lP[7].first, _lP[7].second) << getCornerSticker(_lP[8].first, _lP[8].second) << smallSpace
        << getCornerSticker(_fP[6].first, _fP[6].second) << getEdgeSticker(_fP[7].first, _fP[7].second) << getCornerSticker(_fP[8].first, _fP[8].second) << smallSpace
        << getCornerSticker(_rP[6].first, _rP[6].second) << getEdgeSticker(_rP[7].first, _rP[7].second) << getCornerSticker(_rP[8].first, _rP[8].second) << smallSpace
        << getCornerSticker(_bP[6].first, _bP[6].second) << getEdgeSticker(_bP[7].first, _bP[7].second) << getCornerSticker(_bP[8].first, _bP[8].second) << std::endl << std::endl;;

    std::cout << space << getCornerSticker(_dP[0].first, _dP[0].second) << getEdgeSticker(_dP[1].first, _dP[1].second) << getCornerSticker(_dP[2].first, _dP[2].second) << std::endl << std::endl;
    std::cout << space << getCornerSticker(_dP[3].first, _dP[3].second) << WHITE << "  " << RESET << "  " << getCornerSticker(_dP[5].first, _dP[5].second) << std::endl << std::endl;
    std::cout << space << getCornerSticker(_dP[6].first, _dP[6].second) << getEdgeSticker(_dP[7].first, _dP[7].second) << getCornerSticker(_dP[8].first, _uP[8].second) << std::endl << std::endl;

}