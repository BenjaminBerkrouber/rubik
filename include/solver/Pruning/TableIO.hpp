#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

namespace pruning {
namespace io {

bool save(const std::string& filename, const std::vector<uint8_t>& table, uint8_t id);
bool load(const std::string& filename, std::vector<uint8_t>& table, uint8_t expectedId);

} // namespace io
} // namespace pruning
