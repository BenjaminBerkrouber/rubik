#pragma once

#include "Constants.hpp"
#include <cstdint>

struct CubeState
{
    uint64_t edges = EDGES_SOLVED_STATE;
    uint64_t corners = CORNERS_SOLVED_STATE;
};