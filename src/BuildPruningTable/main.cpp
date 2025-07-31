void generateG1PruningOrientation() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("g1_corners_edges.prune", table, 0x01))
        return;

    auto newTable = TableGenerator::generate(
        encodeOrientationIndex,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        2048 * 2187
    );
    pruning::io::save("g1_corners_edges.prune", newTable, 0x01);
}

void generateG1PruningMSlice() {
    SpinManager spinManager;

    std::vector<uint8_t> table;
    if (pruning::io::load("g1_Mslice.prune", table, 0x02))
        return;

    auto newTable = TableGenerator::generate(
        encodeMSlice,
        [&spinManager](CubeState& state, SpinLst move) {
            spinManager.applyMove(state, move);
        },
        495
    );
    pruning::io::save("g1_Mslice.prune", newTable, 0x02);
}

int main() {
    generateG1PruningOrientation();
    generateG1PruningMSlice();
    return 0;
}