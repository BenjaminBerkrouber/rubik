#pragma once

#include "SpinFunctions.hpp"
#include "Spin.hpp"
#include "Constants.hpp"

using SpinFunction = void(*)(CubeState&);

extern SpinFunction spinTable[SPIN_COUNT];

inline void applyMove(CubeState& state, SpinLst spin) {
    spinTable[spin](state);
}
