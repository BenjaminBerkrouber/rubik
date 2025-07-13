#pragma once


#define YELLOW "\e[43m"
#define WHITE "\e[47m"
#define RED "\e[41m"
#define ORANGE "\e[45m"
#define GREEN "\e[42m"
#define BLUE "\e[44m"
#define RESET "\033[0m"

#include <cstdint>
#include <stdexcept>
#include <array>


#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

#include "./Cube.hpp"

class CubePrinter {

public:
    CubePrinter(Cube &cube);
    ~CubePrinter();


    void print() ;
    std::string getCornerSticker(uint8_t cornerIndex, uint8_t cornerOrientation) const;
    std::string getEdgeSticker(uint8_t edgeIndex, uint8_t edgeOrientation) const;
    std::string getLine(std::pair<uint8_t, uint8_t>& left, std::pair<uint8_t, uint8_t>& center, std::pair<uint8_t, uint8_t>& right);
    std::string getMiddleLine(std::pair<uint8_t, uint8_t>& left, const std::string& color, std::pair<uint8_t, uint8_t>& right);

private:

    Cube &cube;

    /* =============================================================================

        Cube Stickers Mapping:
        =======================
        Used for mapping the colors of the stickers on the cube's pieces.
        Each piece type (corner or edge) is mapped to a vector of strings representing 
        the colors
        of the stickers on that piece. The colors are represented as strings for easy 
        printing.
        The mapping is used to retrieve the colors of the stickers based 
        on the piece index and orientation.
        
    ============================================================================== */

    /*
        * Mapping of corner and edge stickers to their colors.
        * Each entry in the map corresponds to a piece type (corner or edge)
        * and contains a vector of strings representing the colors of the stickers.
        * 
        * For corners, the vector has 3 colors (one for each sticker).
        * For edges, the vector has 2 colors (one for each sticker).
    */
    std::map<uint8_t, std::vector<std::string>> mapping_corners;
    std::map<uint8_t, std::vector<std::string>> mapping_edges;

    void initializeMapping();

    /*
        * Pairs of indices for each face of the cube.
        * Each pair represents a piece on the face, with the first element being the index
        * and the second element being the orientation.
        * 
        * The pairs are used to access the pieces in the cube's representation.
    */
    std::pair<uint8_t, uint8_t> uP[9] = { 
        {2, 0}, {2, 0}, {3, 0}, 
        {1, 0}, {0, 0}, {3, 0},
        {1, 0}, {0, 0}, {0, 0} 
    };
    std::pair<uint8_t, uint8_t> dP[9] = { 
        {5, 0}, {8, 0}, {4, 0}, 
        {9, 0}, {0, 0}, {11, 0},
        {6, 0}, {10, 0}, {7, 0} 
    };
    std::pair<uint8_t, uint8_t> fP[9] = { 
        {1, 2}, {0, 1}, {0, 1}, 
        {5, 0}, {0, 0}, {4, 0},
        {5, 1}, {8, 1}, {4, 2}  
    };
    std::pair<uint8_t, uint8_t> lP[9] = { 
        {2, 2}, {1, 1}, {1, 1}, 
        {6, 1}, {0, 0}, {5, 1},
        {6, 1}, {9, 1}, {5, 2} 
    };
    std::pair<uint8_t, uint8_t> rP[9] = { 
        {0, 2}, {3, 1}, {3, 1}, 
        {4, 1}, {0, 0}, {7, 1},
        {4, 1}, {11, 1}, {7, 2} 
    };
    std::pair<uint8_t, uint8_t> bP[9] = { 
        {3, 2}, {2, 1}, {2, 1}, 
        {7, 0}, {0, 0}, {6, 0},
        {7, 1}, {10, 1}, {6, 2} 
    };
};

void applySpin(Cube& cube, CubePrinter printer, SpinId id, bool verbose);
