#include "../../include/cube/SpinFunctions.hpp"
#include "../../include/cube/CubeOperations.hpp"

void u(CubeState &state) {
    pM(state.edges, 0, 1);
    pM(state.edges, 0, 2);
    pM(state.edges, 0, 3);

    pM(state.corners, 0, 1);
    pM(state.corners, 0, 2);
    pM(state.corners, 0, 3);
}

void u2(CubeState &state) {
    (void)state;
}

void u3(CubeState &state) {
    (void)state;
}
