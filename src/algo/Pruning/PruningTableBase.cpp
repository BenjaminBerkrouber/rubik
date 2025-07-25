#include "../../include/Pruning/PruningTableBase.hpp"

PruningTableBase::PruningTableBase() { 
    table_.fill(0xFF); 
}

void PruningTableBase::writeToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << filename << " pour écriture.\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(table_.data()), table_.size());
    file.close();
}

bool PruningTableBase::readFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier " << filename << " pour lecture.\n";
        return false;
    }
    file.read(reinterpret_cast<char*>(table_.data()), table_.size());
    if (!file) {
        std::cerr << "Erreur lors de la lecture complète du fichier " << filename << ".\n";
        file.close();
        return false;
    }
    file.close();
    return true;
}

uint8_t PruningTableBase::operator[](int index) const {
    return table_[index];
}

int PruningTableBase::maxDepth() const {
    return *std::max_element(table_.begin(), table_.end());
}