#pragma once
#include <vector>
#include <string>
#include <fstream>

template<typename IndexType = size_t>
class PruningTable {
public:

    uint8_t get(IndexType idx) const {
        if (idx >= table.size()) return 0xFF;
        return table[idx];
    }

    size_t size() const {
        return table.size();
    }

private:
    std::vector<uint8_t> table;
};
