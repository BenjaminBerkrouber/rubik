#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <array>
#include <algorithm>

#include "../spin/Spin.hpp"
#include "../utils/Constants.hpp"
#include "../utils/utils.h"


/**
 * @struct ParseResult
 * @brief Represents the result of a parsing operation.
 *
 * @var ok Indicates whether the parsing succeeded.
 * @var message Error message in case of failure.
 */
struct ParseResult {
    bool ok;
    std::string message;
};

/**
 * @class Parser
 * @brief Handles parsing of Rubik's Cube move strings into SpinLst tokens.
 *
 * The Parser class takes an input string like "U R' D2" and converts it into a sequence
 * of SpinLst instructions that can be used programmatically.
 */
class Parser {
    private:
        std::vector<SpinLst> _results; ///< Stores the successfully parsed spin instructions.

        /**
        * @brief Splits a string by a given delimiter character.
        * @param str The input string to split.
        * @param delimiter The character used to separate tokens.
        * @return A vector of string views representing the tokens.
        */
        std::vector<std::string_view> split(const std::string& str, char delimiter) const;

        /**
        * @brief Attempts to convert a token into a SpinLst value.
        * @param token The move string to interpret (e.g., "R", "U'", "D2").
        * @param out Reference to store the result if the conversion is successful.
        * @return True if the token was valid and converted; false otherwise.
        */
        bool tryGetSpinFromString(std::string_view token, SpinLst& out) const;

    public:
        /**
        * @brief Default constructor.
        */
        Parser();

        /**
        * @brief Parses the input string into a sequence of SpinLst instructions.
        * @param input The input string containing cube moves (e.g., "U R' D2").
        * @return A ParseResult indicating success or failure, and an optional error message.
        */
        const ParseResult parse(const std::string& input);

        /**
        * @brief Returns the list of successfully parsed SpinLst instructions.
        * @return A const reference to the vector of parsed SpinLst values.
        */
        const std::vector<SpinLst>& getResults() const;

        /**
        * @brief Clears the results of the parser.
        */
        void clearResults();

        /**
        * @brief Sets the results of the parser to a specific vector of SpinLst values.
        * @param results The vector of SpinLst values to set.
        */
        void setResults(const std::vector<SpinLst>& results);

        /**
        * @brief Generates a vector of random SpinLst instructions.
        * @param count The number of random SpinLst instructions to generate.
        * @return A vector containing the generated SpinLst instructions.
        */
        std::vector<SpinLst> & generateRandomSpinLst(int count);
};
