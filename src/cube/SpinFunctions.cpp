#include "../../include/cube/SpinFunctions.hpp"
#include "../../include/cube/CubeOperations.hpp"

#include <iostream>

void u(CubeState &state) {
    pM(state.corners, 0, 1);
    pM(state.corners, 0, 2);
    pM(state.corners, 0, 3);

    pM(state.edges, 0, 1);
    pM(state.edges, 0, 2);
    pM(state.edges, 0, 3);
}

void u2(CubeState &state) {
    pM(state.corners, 0, 2);
    pM(state.corners, 1, 3);

    pM(state.edges, 0, 2);
    pM(state.edges, 1, 3);
}

void u3(CubeState &state) {
    pM(state.corners, 0, 3);
    pM(state.corners, 0, 2);
    pM(state.corners, 0, 1);

    pM(state.edges, 0, 3);
    pM(state.edges, 0, 2);
    pM(state.edges, 0, 1);
}





void d(CubeState &state) {
    pM(state.corners, 4, 5);
    pM(state.corners, 4, 6);
    pM(state.corners, 4, 7);

    pM(state.edges, 8, 9);
    pM(state.edges, 8, 10);
    pM(state.edges, 8, 11);

}

void d2(CubeState &state) {
    pM(state.corners, 4, 6);
    pM(state.corners, 5, 7);

    pM(state.edges, 8, 10);
    pM(state.edges, 9, 11);
}

void d3(CubeState &state) {
    pM(state.corners, 4, 7);
    pM(state.corners, 4, 6);
    pM(state.corners, 4, 5);

    pM(state.edges, 8, 11);
    pM(state.edges, 8, 10);
    pM(state.edges, 8, 9);
}





void f(CubeState &state) {
    pM(state.corners, 0, 4);
    pM(state.corners, 0, 5);
    pM(state.corners, 0, 1);

    cOm(state.corners, 0, 1);
    cOm(state.corners, 1, 2);
    cOm(state.corners, 4, 2);
    cOm(state.corners, 5, 1);

    pM(state.edges, 0, 4);
    pM(state.edges, 0, 8);
    pM(state.edges, 0, 5);

    eOm(state.edges, 0);
    eOm(state.edges, 4);
    eOm(state.edges, 8);
    eOm(state.edges, 5);
}

void f2(CubeState &state) {
    pM(state.corners, 0, 5);
    pM(state.corners, 4, 1);

    pM(state.edges, 0, 8);
    pM(state.edges, 4, 5);

}

void f3(CubeState &state) {
    pM(state.corners, 0, 1);
    pM(state.corners, 0, 5);
    pM(state.corners, 0, 4);

    cOm(state.corners, 0, 1);
    cOm(state.corners, 1, 2);
    cOm(state.corners, 4, 2);
    cOm(state.corners, 5, 1);

    pM(state.edges, 0, 5);
    pM(state.edges, 0, 8);
    pM(state.edges, 0, 4);

    eOm(state.edges, 0);
    eOm(state.edges, 4);
    eOm(state.edges, 8);
    eOm(state.edges, 5);
}





void b(CubeState &state) {
    pM(state.corners, 2, 6);
    pM(state.corners, 2, 7);
    pM(state.corners, 2, 3);

    cOm(state.corners, 2, 1);
    cOm(state.corners, 3, 2);
    cOm(state.corners, 6, 2);
    cOm(state.corners, 7, 1);

    pM(state.edges, 2, 6);
    pM(state.edges, 2, 10);
    pM(state.edges, 2, 7);

    eOm(state.edges, 2);
    eOm(state.edges, 6);
    eOm(state.edges, 7);
    eOm(state.edges, 10);
}

void b2(CubeState &state) {
    pM(state.corners, 2, 7);
    pM(state.corners, 3, 6);

    pM(state.edges, 2, 10);
    pM(state.edges, 6, 7);
}

void b3(CubeState &state) {
    pM(state.corners, 2, 3);
    pM(state.corners, 2, 7);
    pM(state.corners, 2, 6);

    cOm(state.corners, 2, 2);
    cOm(state.corners, 3, 2);
    cOm(state.corners, 6, 1);
    cOm(state.corners, 7, 1);

    pM(state.edges, 2, 7);
    pM(state.edges, 2, 10);
    pM(state.edges, 2, 6);

    eOm(state.edges, 2);
    eOm(state.edges, 6);
    eOm(state.edges, 7);
    eOm(state.edges, 10);
}





void l(CubeState &state) {
    pM(state.corners, 1, 5);
    pM(state.corners, 1, 6);
    pM(state.corners, 1, 2);

    cOm(state.corners, 1, 1);
    cOm(state.corners, 2, 2);
    cOm(state.corners, 5, 2);
    cOm(state.corners, 6, 1);

    pM(state.edges, 1, 5);
    pM(state.edges, 1, 9);
    pM(state.edges, 1, 6);
}

void l2(CubeState &state) {
    pM(state.corners, 1, 6);
    pM(state.corners, 2, 5);

    pM(state.edges, 1, 9);
    pM(state.edges, 5, 6);
}

void l3(CubeState &state) {
    pM(state.corners, 1, 2);
    pM(state.corners, 1, 6);
    pM(state.corners, 1, 5);

    cOm(state.corners, 1, 1);
    cOm(state.corners, 2, 2);
    cOm(state.corners, 5, 2);
    cOm(state.corners, 6, 1);

    pM(state.edges, 1, 6);
    pM(state.edges, 1, 9);
    pM(state.edges, 1, 5);
}





void r(CubeState &state) {
    pM(state.corners, 0, 3);
    pM(state.corners, 0, 7);
    pM(state.corners, 0, 4);

    cOm(state.corners, 0, 2);
    cOm(state.corners, 3, 1);
    cOm(state.corners, 4, 1);
    cOm(state.corners, 7, 2);

    pM(state.edges, 4, 3);
    pM(state.edges, 4, 7);
    pM(state.edges, 4, 11);
}

void r2(CubeState &state) {
    pM(state.corners, 0, 7);
    pM(state.corners, 3, 4);

    pM(state.edges, 4, 7);
    pM(state.edges, 3, 11);
}

void r3(CubeState &state) {
    pM(state.corners, 0, 4);
    pM(state.corners, 0, 7);
    pM(state.corners, 0, 3);

    cOm(state.corners, 0, 2);
    cOm(state.corners, 3, 1);
    cOm(state.corners, 4, 1);
    cOm(state.corners, 7, 2);

    pM(state.edges, 4, 11);
    pM(state.edges, 4, 7);
    pM(state.edges, 4, 3);
}
