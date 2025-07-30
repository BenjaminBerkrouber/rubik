#include "../../include/Pruning/PruningOrientedCorner.hpp"

using PruningTable = std::array<uint8_t, 2187>;

int PruningOrientedCorner::encodeCornersOrientation(const std::array<uint8_t, 8>& corners_orientation) {
    int idx = 0;
    for (int i = 0; i < 7; ++i) {
        idx = idx * 3 + corners_orientation[i];
    }
    return idx;
}

std::array<uint8_t, 8> PruningOrientedCorner::decodeCornersOrientation(int index) {
    std::array<uint8_t, 8> orientation;
    int sum = 0;
    for (int i = 6; i >= 0; --i) {
        orientation[i] = index % 3;
        sum += orientation[i];
        index /= 3;
    }
    orientation[7] = (3 - (sum % 3)) % 3;
    return orientation;
}


void    PruningOrientedCorner::generateTable(Cube& cube) {
    table_.fill(0xFF);

    std::queue<int> q;

    int solvedIndex = encodeCornersOrientation(cube.getCornerOrientations());
    table_[solvedIndex] = 0;
    q.push(solvedIndex);

    while (!q.empty()) {
        int currentIndex = q.front();
        q.pop();

        auto currentOrientation = decodeCornersOrientation(currentIndex);

        for (const auto& spinId : allowedSpins_) {
            Cube tempCube;
            tempCube.setCornerOrientations(currentOrientation);
            tempCube.applySpin(spinId);

            int nextIndex = encodeCornersOrientation(tempCube.getCornerOrientations());

            if (table_[nextIndex] == 0xFF) {
                table_[nextIndex] = table_[currentIndex] + 1;
                q.push(nextIndex);
            }
        }
    }

    std::cout << "Pruning table generated (max depth = " << maxDepth() << ")\n";
}


void  PruningOrientedCorner::writePruningTableToBinaryFile(const PruningTable& table, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << filename << " pour écriture.\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(table.data()), table.size());
    file.close();
}


PruningTable  PruningOrientedCorner::readPruningTableFromBinaryFile(const std::string& filename) {
    PruningTable table{};
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << filename << " pour lecture.\n";
        return table;
    }
    file.read(reinterpret_cast<char*>(table.data()), table.size());
    if (!file) {
        std::cerr << "Erreur lors de la lecture complète du fichier " << filename << ".\n";
    }
    file.close();
    return table;
}
