#pragma once

/**
 * @enum SpinLst
 * @brief Enumeration of all possible Rubik's Cube face moves.
 *
 * This enum defines all 18 possible face rotations on a Rubik's Cube.
 * Each move corresponds to a clockwise (e.g., `U`), double (`U2`), or counterclockwise (`U3`) rotation.
 *
 * The moves are grouped by face:
 * - U: Up
 * - D: Down
 * - F: Front
 * - B: Back
 * - L: Left
 * - R: Right
 *
 * Naming convention:
 * - `X`  → Clockwise 90° rotation of face X
 * - `X2` → 180° rotation of face X
 * - `X3` → Counterclockwise 90° rotation of face X
 */
enum SpinLst {
    U,  ///< Up face - 90° clockwise
    U2, ///< Up face - 180°
    U3, ///< Up face - 90° counterclockwise

    D,  ///< Down face - 90° clockwise
    D2, ///< Down face - 180°
    D3, ///< Down face - 90° counterclockwise

    F,  ///< Front face - 90° clockwise
    F2, ///< Front face - 180°
    F3, ///< Front face - 90° counterclockwise

    B,  ///< Back face - 90° clockwise
    B2, ///< Back face - 180°
    B3, ///< Back face - 90° counterclockwise

    L,  ///< Left face - 90° clockwise
    L2, ///< Left face - 180°
    L3, ///< Left face - 90° counterclockwise

    R,  ///< Right face - 90° clockwise
    R2, ///< Right face - 180°
    R3  ///< Right face - 90° counterclockwise
};
