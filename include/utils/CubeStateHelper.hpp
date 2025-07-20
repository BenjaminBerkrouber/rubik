#pragma once

#include "../cube/CubeState.hpp"
#include <string>
#include <array>
#include <stdexcept>

#define YELLOW "\e[43m"
#define WHITE "\e[47m"
#define RED "\e[41m"
#define ORANGE "\e[45m"
#define GREEN "\e[42m"
#define BLUE "\e[44m"
#define RESET "\033[0m"

enum CornersPieceLst {
    URF,
    UFL,
    ULB,
    UBR,
    DFR,
    DLF,
    DBL,
    DRB
};

enum EdgesPieceLst {
    UF,
    UL,
    UB,
    UR,
    FR,
    FL,
    BL,
    BR,
    DF,
    DL,
    DB,
    DR
};

enum Color {
    e_YELLOW,
    e_BLUE,
    e_RED,
    e_GREEN,
    e_ORANGE,
    e_WHITE
};

class CornersPiece {
    private:
        int _name;
        std::array<int, 3> _colors;

    public:
        CornersPiece(std::array<int, 3> colors, int name)
            : _name(name), _colors(colors) {}

        ~CornersPiece() = default;

        int getColor(int i) const {
            if (i < 0 || i >= 3)
                throw std::out_of_range("Invalid index for corner piece color");
            return _colors[i];
        }

        int getName() const {
            return _name;
        }
};

// class Face {
//     private:

//     public:
    
// }

class EdgesPiece {
        private:
        int _name;
        std::array<int, 2> _colors;

    public:
        EdgesPiece(std::array<int, 2>  colors, int name)
            : _name(name), _colors(colors) {}

        ~EdgesPiece() = default;

        int getColor(int i) const {
            if (i < 0 || i >= 2)
                throw std::out_of_range("Invalid index for corner piece color");
            return _colors[i];
        }

        int getName() const {
            return _name;
        }
};

class CubeStateHelper  {

    private:
        CubeState _cube;
        std::array<CornersPiece, 8> _corners;
        std::array<EdgesPiece, 12> _edges;



        std::pair<uint8_t, uint8_t> _uP[9] = { 
            {ULB, 0}, {UB, 0}, {UBR, 0}, 
            {UL, 0}, {0, 0}, {UR, 0},
            {UFL, 0}, {UF, 0}, {URF, 0} 
        };
        std::pair<uint8_t, uint8_t> _dP[9] = { 
            {DLF, 0}, {DF, 0}, {DFR, 0}, 
            {DL, 0}, {0, 0}, {DR, 0},
            {DBL, 0}, {DB, 0}, {DRB, 0} 
        };
        std::pair<uint8_t, uint8_t> _fP[9] = { 
            {UFL, 1}, {UF, 1}, {URF, 2}, 
            {FL, 0}, {0, 0}, {FR, 0},
            {DLF, 1}, {DF, 1}, {DFR, 2}  
        };
        std::pair<uint8_t, uint8_t> _lP[9] = { 
            {ULB, 1}, {UL, 1}, {UFL, 2}, 
            {BL, 1}, {0, 0}, {FL, 1},
            {DLF, 1}, {DL, 1}, {5, 2} 
        };
        std::pair<uint8_t, uint8_t> _rP[9] = { 
            {0, 2}, {3, 1}, {3, 1}, 
            {4, 1}, {0, 0}, {7, 1},
            {4, 1}, {11, 1}, {7, 2} 
        };
        std::pair<uint8_t, uint8_t> _bP[9] = { 
            {3, 2}, {2, 1}, {2, 1}, 
            {7, 0}, {0, 0}, {6, 0},
            {7, 1}, {10, 1}, {6, 2} 
        };

        std::string getCornerSticker(int i, int o);
        std::string getEdgeSticker(int i, int o);
    public:
        CubeStateHelper(const CubeState &cube);
        ~CubeStateHelper();

        void printState();
        void printCube();
};