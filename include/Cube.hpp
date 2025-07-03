#pragma once
#include "./SpinLib.hpp"

class Cube {
    public:
    
        Cube();
        ~Cube();


        void applySpin(SpinId id);




        const std::array<uint8_t, 8> &getCorners() const;
        const std::array<uint8_t, 8> &getCornerOrientations() const; 
        const std::array<uint8_t, 12> &getEdges() const; 
        const std::array<uint8_t, 12> &getEdgeOrientations() const;

        void setCorners(const std::array<uint8_t, 8>& new_corners);
        void setCornerOrientations(const std::array<uint8_t, 8>& new_corners_orientation);
        void setEdges(const std::array<uint8_t, 12>& new_edges);
        void setEdgeOrientations(const std::array<uint8_t, 12>& new_edges_orientation);

    private:

        SpinLib& spinLib = SpinLib::getInstance();

        void applySimpleMove(auto &dest, auto &dest_orientation, const auto& moves, int mod);
        void applyDoubleMove(auto& dest, auto &dest_orientation, const auto& moves, int mod);

    /* =============================================================================

        Cube Representation:
        =======================

        This class represents a Rubik's Cube with its pieces and orientations.
        It contains arrays for corners and edges, each with their respective orientations.
        
    ============================================================================== */


        /*
            * Cube representation:
            * 
            *  Corners: 8 pieces, each with 3 stickers
            *  Edges: 12 pieces, each with 2 stickers
            * 
            *  Each piece has an index and an orientation.
            *  Corners can be oriented in 3 ways, edges in 2 ways.
            * 
            *  The mapping is stored in a map for easy access.
        */
        std::array<uint8_t, 8> corners;
        std::array<uint8_t, 8> corners_orientation;

        std::array<uint8_t, 12> edges;
        std::array<uint8_t, 12> edges_orientation;
};