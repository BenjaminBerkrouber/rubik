#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <stdexcept>


/*
 * Permutation struct
 *
 * Represents a permutation of cube pieces, where 'from' is the index of the piece being moved,
 * and 'to' is the index of the piece it is moved to.
 *    * Example: {from: 1, to: 5} means the piece at index 1 is moved to index 5.
*/
struct Permutation {
    uint8_t from;
    uint8_t to;
};

/*
 * OrientationChange struct
 *
 * Represents a change in orientation for a cube piece, where 'index' is the index of the piece,
 * and 'delta' is the change in orientation.
    * Example: {index: 1, delta: 2} means the piece at index 1 has its orientation changed by 2.
*/
struct OrientationChange {
    uint8_t index;
    uint8_t delta;
};


/*
 * Spin struct
 *
 * Represents a spin in the Rubik's Cube, containing moves and orientation changes for corners and edges.
 * - cornersMoves: A vector of Permutation structs representing the moves of corner pieces.
 * - cornersOrientation: A vector of OrientationChange structs representing the orientation changes of corner pieces.
 * - edgesMoves: A vector of Permutation structs representing the moves of edge pieces.
 * - edgesOrientation: A vector of OrientationChange structs representing the orientation changes of edge pieces.
*/
struct Spin {
    
    std::vector<Permutation> cornersMoves;
    std::vector<OrientationChange> cornersOrientation;
    
    std::vector<Permutation> edgesMoves;
    std::vector<OrientationChange> edgesOrientation;
};


/* ==============================================================================
    *
    * SpinLib class
    *
    * Singleton class that manages a library of spins for the Rubik's Cube.
    * It initializes a set of predefined spins and provides access to them by name.
    * 
    * Usage:
    *   SpinLib& spinLib = SpinLib::getInstance();
    *   const Spin& spin = spinLib.getSpin("U");
    * 
    * This class is designed to be a singleton, ensuring that only one instance exists throughout the application.
    * It provides a method to retrieve spins by their name, which can be used to apply
    * specific moves to a Rubik's Cube.
    *
=============================================================================== */
class SpinLib {

    
    public:

        SpinLib();
        ~SpinLib();
        

        /*
         * getInstance
         *
         * Returns the singleton instance of SpinLib.
         * This method ensures that only one instance of SpinLib exists throughout the application.
         *
         * @return SpinLib& - Reference to the singleton instance of SpinLib.
        */
        static SpinLib& getInstance();

        /*
         * getSpin
         *
         * Retrieves a Spin object by its name.
         * Throws an exception if the spin name does not exist in the library.
         * @param spinName - The name of the spin to retrieve.
         * @return const Spin& - A constant reference to the Spin object associated with the given name.
         * @throws std::invalid_argument - If the spin name does not exist in the library.
        */
        const Spin& getSpin(const std::string& spinName) const;

    private:

        /* 
         * spins
         *
         * A map that holds the predefined spins, where the key is the name of the spin (e.g., "U", "D'", "L2")
         * and the value is a Spin object containing the moves and orientation changes for corners and edges
        */
        std::unordered_map<std::string, Spin> spins;

        /*
         * initializeSpins
         *
         * Initializes the spins map with predefined spins.
         * This method populates the spins map with various Rubik's Cube spins,
         * defining the moves and orientation changes for corners and edges.
        */
        void initializeSpins();
};
