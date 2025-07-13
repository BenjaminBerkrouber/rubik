#pragma once

#include "./CubeState.hpp"

/**
 * @brief Applies a clockwise 90-degree rotation of the Up face to the given CubeState.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 * @param state The CubeState to modify.
 */
void u(CubeState &state);

/**
 * @brief Applies a 180-degree rotation of the Up face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void u2(CubeState &state);

/**
 * @brief Applies a counterclockwise 90-degree rotation of the Up face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void u3(CubeState &state);

/**
 * @brief Applies a clockwise 90-degree rotation of the Down face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void d(CubeState &state);

/**
 * @brief Applies a 180-degree rotation of the Down face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void d2(CubeState &state);

/**
 * @brief Applies a counterclockwise 90-degree rotation of the Down face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void d3(CubeState &state);

/**
 * @brief Applies a clockwise 90-degree rotation of the Front face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void f(CubeState &state);

/**
 * @brief Applies a 180-degree rotation of the Front face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void f2(CubeState &state);

/**
 * @brief Applies a counterclockwise 90-degree rotation of the Front face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void f3(CubeState &state);

/**
 * @brief Applies a clockwise 90-degree rotation of the Back face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void b(CubeState &state);

/**
 * @brief Applies a 180-degree rotation of the Back face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void b2(CubeState &state);

/**
 * @brief Applies a counterclockwise 90-degree rotation of the Back face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void b3(CubeState &state);

/**
 * @brief Applies a clockwise 90-degree rotation of the Left face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void l(CubeState &state);

/**
 * @brief Applies a 180-degree rotation of the Left face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void l2(CubeState &state);

/**
 * @brief Applies a counterclockwise 90-degree rotation of the Left face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void l3(CubeState &state);

/**
 * @brief Applies a clockwise 90-degree rotation of the Right face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void r(CubeState &state);

/**
 * @brief Applies a 180-degree rotation of the Right face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void r2(CubeState &state);

/**
 * @brief Applies a counterclockwise 90-degree rotation of the Right face.
 *
 * This function modifies the CubeState in-place to simulate a clockwise rotation of the Up face.
 * It uses bitwise operations to permute edge and corner positions (via `pM`),
 * and adjust their orientations if necessary (via `eOm` and `cOm`).
 *
 *  @param state The CubeState to modify.
 */
void r3(CubeState &state);

