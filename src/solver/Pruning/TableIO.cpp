#include "../../../include/solver/Pruning/TableIO.hpp"

namespace pruning {
    namespace io {

        bool save(const std::string& filename, const std::vector<uint8_t>& table, uint8_t id) {
            std::ofstream out(filename, std::ios::binary);
            if (!out.is_open()) return false;

            out.write(reinterpret_cast<const char*>(&id), 1);
            out.write(reinterpret_cast<const char*>(table.data()), table.size());
            return out.good();
        }

        bool load(const std::string& filename, std::vector<uint8_t>& table, uint8_t expectedId) {
            std::ifstream in(filename, std::ios::binary);
            if (!in.is_open()) return false;

            uint8_t actualId = 0;
            in.read(reinterpret_cast<char*>(&actualId), 1);
            if (actualId != expectedId) return false;

            table.assign(std::istreambuf_iterator<char>(in), {});
            return true;
        }

    } // namespace io
} // namespace pruning
