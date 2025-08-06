#pragma once

#include "../cube/CubeState.hpp"
#include "../engine/IEngine.hpp"
#include <string>
#include <array>
#include <stdexcept>

#define YELLOW "\e[43m"
#define WHITE "\e[47m"
#define RED "\e[41m"
#define ORANGE "\e[48;5;208m" 
#define GREEN  "\e[48;5;34m"  
#define BLUE "\e[44m"
#define RESET "\033[0m"




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
                throw std::out_of_range("Invalid index for corner piece color" + std::to_string(i));
            return _colors[i];
        }

        std::string getName() const {
            switch (_name) {
                case URF: return "URF";
                case UFL: return "UFL";
                case ULB: return "ULB";
                case UBR: return "UBR";
                case DFR: return "DFR";
                case DLF: return "DLF";
                case DBL: return "DBL";
                case DRB: return "DRB";
                default:
                    return "Unknown " + std::to_string(_name);
            }
        }
};


class EdgesPiece {
    private:
        int _name;
        std::array<int, 2> _colors;

    public:
        EdgesPiece(std::array<int, 2>  colors, int name)
            : _name(name), _colors(colors) {}

        ~EdgesPiece() = default;

        int getColor(int i) const {
            if (i < 0 || i > 1)
                throw std::out_of_range("Invalid index for edge piece color" + std::to_string(i));
            return _colors[i];
        }

        std::string getName() const {
            switch (_name) {
                case UF: return "UF";
                case UL: return "UL";
                case UB: return "UB";
                case UR: return "UR";
                case FR: return "FR";
                case FL: return "FL";
                case BL: return "BL";
                case BR: return "BR";
                case DF: return "DF";
                case DL: return "DL";
                case DB: return "DB";
                case DR: return "DR";
                default: 
                    return "Unknown " + std::to_string(_name);
            }
        }
};

class CubeStateHelper : public IEngine {

    private:
        CubeState& _cube;
        std::array<CornersPiece, 8> _corners;
        std::array<EdgesPiece, 12> _edges;

        const std::pair<uint8_t, uint8_t> _uP[9] = { 
            {ULB, 0}, {UB, 0}, {UBR, 0}, 
            {UL, 0}, {0, 0}, {UR, 0},
            {UFL, 0}, {UF, 0}, {URF, 0} 
        };
        const std::pair<uint8_t, uint8_t> _dP[9] = { 
            {DLF, 0}, {DF, 0}, {DFR, 0}, 
            {DL, 0}, {0, 0}, {DR, 0},
            {DBL, 0}, {DB, 0}, {DRB, 0} 
        };
        const std::pair<uint8_t, uint8_t> _fP[9] = { 
            {UFL, 1}, {UF, 1}, {URF, 2}, 
            {FL, 0}, {0, 0}, {FR, 0},
            {DLF, 2}, {DF, 1}, {DFR, 1}  
        };
        const std::pair<uint8_t, uint8_t> _lP[9] = { 
            {ULB, 1}, {UL, 1}, {UFL, 2}, 
            {BL, 1}, {0, 0}, {FL, 1},
            {DBL, 2}, {DL, 1}, {DLF, 1} 
        };
        const std::pair<uint8_t, uint8_t> _rP[9] = { 
            {URF, 1}, {UR, 1}, {UBR, 2}, 
            {FR, 1}, {0, 0}, {BR, 1},
            {DFR, 2}, {DR, 1}, {DRB, 1} 
        };
        const std::pair<uint8_t, uint8_t> _bP[9] = { 
            {UBR, 1}, {UB, 1}, {ULB, 2}, 
            {BR, 0}, {0, 0}, {BL, 0},
            {DRB, 2}, {DB, 1}, {DBL, 1} 
        };



        std::string getCcolor(int i, int o) const;
        std::string getEColor(int i, int o) const;
        std::string getCenter(int i) const;
    public:
        CubeStateHelper(CubeState &cube);
        ~CubeStateHelper();

        void printState() const ;
        void printFace(const std::pair<uint8_t, uint8_t> _face[9], int faceName, std::string padding) const;
        void print() const override;
};