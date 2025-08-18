#include "../../include/spin/SpinManager.hpp"

SpinManager::SpinManager() : _spinTable  {{
        { cycle4, {URF, UFL, ULB, UBR}, {UR, UF, UL, UB}, },
        { cycle2, {URF, UFL, ULB, UBR}, {UR, UF, UL, UB}, },
        { cycle4, {URF, UBR, ULB, UFL}, {UR, UB, UL, UF}, },
        { cycle4, {DFR, DRB, DBL, DLF}, {DF, DR, DB, DL}, },
        { cycle2, {DFR, DRB, DBL, DLF}, {DF, DR, DB, DL}, },
        { cycle4, {DFR, DLF, DBL, DRB}, {DF, DL, DB, DR}, },
        { cycle4, {URF, DFR, DLF, UFL}, {UF, FR, DF, FL}, true, true },
        { cycle2, {URF, DFR, DLF, UFL}, {UF, FR, DF, FL}, },
        { cycle4, {URF, UFL, DLF, DFR}, {UF, FL, DF, FR}, true, true },
        { cycle4, {ULB, DBL, DRB, UBR}, {UB, BL, DB, BR}, true, true },
        { cycle2, {ULB, DBL, DRB, UBR}, {UB, BL, DB, BR}, },
        { cycle4, {ULB, UBR, DRB, DBL}, {UB, BR, DB, BL}, true, true },
        { cycle4, {UFL, DLF, DBL, ULB}, {UL, FL, DL, BL}, true },
        { cycle2, {UFL, DLF, DBL, ULB}, {UL, FL, DL, BL}, },
        { cycle4, {UFL, ULB, DBL, DLF}, {UL, BL, DL, FL}, true },
        { cycle4, {UBR, DRB, DFR, URF}, {UR, BR, DR, FR}, true },
        { cycle2, {UBR, DRB, DFR, URF}, {UR, BR, DR, FR}, },
        { cycle4, {UBR, URF, DFR, DRB}, {UR, FR, DR, BR}, true },
    }}
{}


void SpinManager::applyMove(CubeState& state, SpinLst spin) {
    const SpinDefinition& def = _spinTable.at(spin);
    
    if (def.cycleFunc == nullptr) {
        throw std::runtime_error("Invalid spin function for " + std::to_string(spin));
    }

    def.cycleFunc(state, def.cornersIndex, def.edgeIndex, def.deltaCorners, def.deltaEdges);
}

SpinLst SpinManager::getInverseSpin(SpinLst spin) const {
    int group = static_cast<int>(spin) / 3;
    int pos = static_cast<int>(spin) % 3;
    switch (pos) {
        case 0: return static_cast<SpinLst>(group * 3 + 2);
        case 2: return static_cast<SpinLst>(group * 3 + 0);
        case 1: return static_cast<SpinLst>(group * 3 + 1);
        default:
            throw std::invalid_argument("Invalid spin value");
    }
}
