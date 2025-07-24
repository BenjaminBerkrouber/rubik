#include "../../include/cube/SpinFunctions.hpp"
#include "../../include/cube/CubeOperations.hpp"
#include "../../include/cube/Constants.hpp"

#include <iostream>

void u(CubeState &state) {
    uint8_t corners[4] = {URF, UFL, ULB, UBR};
    uint8_t edges[4] = {UR, UF, UL, UB};

    cycle4(state, corners, edges);
}

void u2(CubeState &state) {
    uint8_t corners[4] = {URF, UFL, ULB, UBR};
    uint8_t edges[4] = {UR, UF, UL, UB};

    cycle2(state, corners, edges);
}

void u3(CubeState &state) {
    uint8_t corners[4] = {URF, UBR, ULB, UFL};
    uint8_t edges[4] = {UR, UB, UL, UF};

    cycle4(state, corners, edges);
}



void d(CubeState &state) {
    uint8_t corners[4] = {DFR, DRB, DBL, DLF};
    uint8_t edges[4] = {DF, DR, DB, DL};

    cycle4(state, corners, edges);
}

void d2(CubeState &state) {
    uint8_t corners[4] = {DFR, DRB, DBL, DLF};
    uint8_t edges[4] = {DF, DR, DB, DL};

    cycle2(state, corners, edges);
}

void d3(CubeState &state) {
    uint8_t corners[4] = {DFR, DLF, DBL, DRB};
    uint8_t edges[4] = {DF, DL, DB, DR};

    cycle4(state, corners, edges);
}




void f(CubeState &state) {
    uint8_t corners[4] = {URF, DFR, DLF, UFL};
    uint8_t edges[4] = {UF, FR, DF, FL};

    cycle4(state, corners, edges, true, true);
}


void f2(CubeState &state) {
    uint8_t corners[4] = {URF, DFR, DLF, UFL};
    uint8_t edges[4] = {UF, FR, DF, FL};

    cycle2(state, corners, edges);
}

void f3(CubeState &state) {
    uint8_t corners[4] = {URF, UFL, DLF, DFR};
    uint8_t edges[4] = {UF, FL, DF, FR};

    cycle4(state, corners, edges, true, true);
}





void b(CubeState &state) {
    uint8_t corners[4] = {ULB, DBL, DRB, UBR};
    uint8_t edges[4] = {UB, BL, DB, BR};

    cycle4(state, corners, edges, true, true);
}

void b2(CubeState &state) {
    uint8_t corners[4] = {ULB, DBL, DRB, UBR};
    uint8_t edges[4] = {UB, BL, DB, BR};

    cycle2(state, corners, edges);
}

void b3(CubeState &state) {
    uint8_t corners[4] = {ULB, UBR, DRB, DBL};
    uint8_t edges[4] = {UB, BR, DB, BL};

    cycle4(state, corners, edges, true, true);
}





void l(CubeState &state) {
    uint8_t corners[4] = {UFL, DLF, DBL, ULB};
    uint8_t edges[4] = {UL, FL, DL, BL};

    cycle4(state, corners, edges, true);
}


void l2(CubeState &state) {
    uint8_t corners[4] = {UFL, DLF, DBL, ULB};
    uint8_t edges[4] = {UL, FL, DL, BL};

    cycle2(state, corners, edges);
}

void l3(CubeState &state) {
    uint8_t corners[4] = {UFL, ULB, DBL, DLF};
    uint8_t edges[4] = {UL, BL, DL, FL};

    cycle4(state, corners, edges, true);
}





void r(CubeState &state) {
    uint8_t corners[4] = {UBR, DRB, DFR, URF};
    uint8_t edges[4] = {UR, BR, DR, FR};

    cycle4(state, corners, edges, true);
}

void r2(CubeState &state) {
    uint8_t corners[4] = {UBR, DRB, DFR, URF};
    uint8_t edges[4] = {UR, BR, DR, FR};

    cycle2(state, corners, edges);
}

void r3(CubeState &state) {
    uint8_t corners[4] = {UBR, URF, DFR, DRB};
    uint8_t edges[4] = {UR, FR, DR, BR};

    cycle4(state, corners, edges, true);
}
