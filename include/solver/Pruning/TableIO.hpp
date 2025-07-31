#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

namespace pruning {
    namespace io {
        
        /**
        * @brief Saves a pruning table to a binary file.
        * 
        * @param filename Destination file path.
        * @param table Pruning table to save.
        * @param id Identifier to store for this version of the table.
        * @return true if the save was successful, false otherwise.
        */
        bool save(const std::string& filename, const std::vector<uint8_t>& table, uint8_t id);

        /**
        * @brief Loads a pruning table from a binary file.
        * 
        * @param filename Source file path.
        * @param table Reference to the vector to fill with loaded data.
        * @param expectedId Expected identifier to validate compatibility.
        * @return true if the load was successful and the identifier matches, false otherwise.
        */
        bool load(const std::string& filename, std::vector<uint8_t>& table, uint8_t expectedId);

    } // namespace io
} // namespace pruning
