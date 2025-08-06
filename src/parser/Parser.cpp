#include "parser/Parser.hpp"

// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================

/**
 * @brief Correspondence table between motion strings and SpinLst values.
 * Sorted for quick binary search.
 */
static constexpr std::array<std::pair<std::string_view, SpinLst>, SPIN_COUNT> kSpinTableSorted {{
    {"B", SpinLst::B}, {"B'", SpinLst::B3}, {"B2", SpinLst::B2},
    {"D", SpinLst::D}, {"D'", SpinLst::D3}, {"D2", SpinLst::D2},
    {"F", SpinLst::F}, {"F'", SpinLst::F3}, {"F2", SpinLst::F2},
    {"L", SpinLst::L}, {"L'", SpinLst::L3}, {"L2", SpinLst::L2},
    {"R", SpinLst::R}, {"R'", SpinLst::R3}, {"R2", SpinLst::R2},
    {"U", SpinLst::U}, {"U'", SpinLst::U3}, {"U2", SpinLst::U2},
}};

Parser::Parser() {}


// ==============================================================================================================================
// ==== Parse Method ====
// ==============================================================================================================================


const ParseResult Parser::parse(const std::string& input) {
    _results.clear();
    if (input.empty()) return ParseResult{false, "Input string is empty"};
    auto tokens = split(input, ' ');
    if (tokens.empty()) return ParseResult{false, "No moves found in input"};

    _results.reserve(tokens.size());
    for (const auto& token : tokens) {
        SpinLst spin;
        if (!tryGetSpinFromString(token, spin)) {
            return ParseResult{false, "Invalid spin token: [" + std::string(token) + "]"};
        }
        _results.push_back(spin);
    }

    return ParseResult{true, ""};
}


// ==============================================================================================================================
// ==== Utils Methods ====
// ==============================================================================================================================


std::vector<std::string_view> Parser::split(const std::string& str, char delimiter) const {
    std::vector<std::string_view> tokens;
    size_t start = 0;
    for (size_t i = 0; i <= str.size(); ++i) {
        if (i == str.size() || str[i] == delimiter) {
            if (i > start)
                tokens.emplace_back(&str[start], i - start);
            start = i + 1;
        }
    }
    return tokens;
}

bool Parser::tryGetSpinFromString(std::string_view token, SpinLst& out) const {
    auto it = std::lower_bound(kSpinTableSorted.begin(), kSpinTableSorted.end(), token,
        [](const auto& p, std::string_view val) {
            return p.first < val;
        });

    if (it != kSpinTableSorted.end() && it->first == token) {
        out = it->second;
        return true;
    }
    return false;
}

std::vector<SpinLst> & Parser::generateRandomSpinLst(int count) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
    _results.clear();
    for (int i = 0; i < count; ++i) {
        SpinLst spin = static_cast<SpinLst>(rand() % static_cast<int>(SPIN_COUNT));
        _results.push_back(spin);
    }
    return _results;
}

void Parser::clearResults() {
    _results.clear();
}


// ==================================================================================
// ==== Getter ====
// ==================================================================================


const std::vector<SpinLst>& Parser::getResults() const {
    return _results;
}


// ==================================================================================
// ==== Setter ====
// ==================================================================================


void Parser::setResults(const std::vector<SpinLst>& results) {
    _results = results;
}