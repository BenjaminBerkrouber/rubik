#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include <stdexcept>

#include <array>
#include <ostream>


/**
 * @enum SpinId
 * @brief   Enumerates all possible basic Rubik's Cube moves.
 *
 *          Each move is represented by a unique identifier, which can be used to retrieve the corresponding Spin object.
 *          The moves include U (Up), D (Down), R (Right), L (Left), F (Front), B (Back) and their inverses and double turns.
*/
enum class SpinId : uint8_t {
    U,
    U_PRIME,
    D,
    D_PRIME,
    R,
    R_PRIME,
    L,
    L_PRIME,
    F,
    F_PRIME,
    B,
    B_PRIME,
    U2,
    L2,
    F2,
    R2,
    D2,
    B2,
    COUNT
};


constexpr size_t to_index(SpinId id) {
    return static_cast<size_t>(id);
}


/**
 * @struct Permutation
 * @brief   Represents a single piece's movement and orientation change due to a spin.
 *
 *          This struct contains:
 *              - from: The index of the piece before the spin.
 *              - to: The index of the piece after the spin.
 *              - delta: The change in orientation (for corners and edges).
*/
struct Permutation {
    uint8_t from;
    uint8_t to;
    uint8_t delta = 0;

    Permutation() = default;

    Permutation(uint8_t from, uint8_t to, uint8_t delta = 0)
        : from(from), to(to), delta(delta) {}
};


/**
 * @struct Spin

 * @brief   Represents a spin in the Rubik's Cube, containing moves for corners and edges.

 *          This struct holds two arrays of Permutation structure:
 *              - cornersMoves: An array of 4 Permutation structure representing the moves for corner pieces.
 *              - edgesMoves: An array of 4 Permutation structure representing the moves for edge pieces.
*/
struct Spin {    
    std::array<Permutation, 4> cornersMoves;
    std::array<Permutation, 4> edgesMoves;

    Spin() = default;

    Spin(std::array<Permutation, 4> const& corners, std::array<Permutation, 4> const& edges)
        : cornersMoves(corners), edgesMoves(edges) {}
};


/**
    * @class SpinLib
    * @brief Singleton class that manages a collection of Spin objects.
    *
    * This class provides access to predefined spins for a Rubik's Cube, allowing users to retrieve
    * spins by their SpinId. It ensures that only one instance of SpinLib exists throughout the application,
    * and initializes the spins with predefined moves for corners and edges.
    * @note The SpinLib class is designed to be a singleton, meaning it can only be instantiated once.
    *       Use SpinLib::getInstance() to access the singleton instance.  
    * @example
    * SpinLib& spinLib = SpinLib::getInstance();
    * const Spin& spin = spinLib.getSpin(SpinId::U);
*/
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
         * Retrieves a Spin object by its SpinId.
         * Throws an out_of_range exception if the SpinId is invalid.
         *
         * @param id - The SpinId for which to retrieve the Spin.
         * @return const Spin& - A reference to the Spin object corresponding to the given id.
         * @throws std::out_of_range if the id is invalid.
        */
        const Spin& getSpin(SpinId id) const;

    private:

        /**
         * spins
         * @brief   Represents a collection of Spin objects indexed by SpinId.
         *          Each Spin object contains the moves for corners and edges for a specific spin.
         * The size of the array is determined by the COUNT value in SpinId, ensuring that it can hold all defined spins.
        */
        std::array<Spin, static_cast<size_t>(SpinId::COUNT)> spins;

        /**
         * initializeSpins
         *
         * Initializes the spins array with predefined spins.
         * This method is called in the constructor to populate the SpinLib with all available spins.
         *
         * It defines the moves for corners and edges for each type of spin.
        */
        void initializeSpins();

        /**
         * addSpin
         *
         * Adds a new Spin to the spins array.
         * @brief This method is used to define the moves for corners and edges for a specific spin.
         *
         * @param id - The SpinId for which to add the Spin.
         * @param cornersMoves - An array of Permutation objects representing corner moves.
         * @param edgesMoves - An array of Permutation objects representing edge moves.
        */
        void addSpin(SpinId id, 
            std::array<Permutation, 4> cornersMoves, 
            std::array<Permutation, 4> edgesMoves
        );
};

