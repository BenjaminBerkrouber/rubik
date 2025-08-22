#include <iostream>
#include <chrono>

#include "include/RubikController.hpp"

#include "include/BuildPruningTable/TableGenerator.hpp"
#include "include/solver/Pruning/TableIO.hpp"
#include "include/cube/Encoding.h"

#include "include/spin/SpinManager.hpp"

#include "include/engine/CubeStateHelper.hpp"
#include "include/utils/Constants.hpp"


#include "include/solver/Kociemba/KociembaSolver.hpp"


#include <unordered_set>
static inline int error(const std::string& message) {
    std::cerr << "[KO] | " << message << std::endl;
    return 1;
}

void exploreAllEncodingsG4() {
    std::unordered_set<uint32_t> seenCodes;
    std::queue<CubeState> queue;
    SpinManager spinManager;

    CubeState solved;
    queue.push(solved);
    seenCodes.insert(encodeG4(solved));

    std::vector<SpinLst> allowedMoves = {
        SpinLst::U2, SpinLst::D2, SpinLst::L2, 
        SpinLst::R2, SpinLst::F2, SpinLst::B2
    };

    uint32_t maxcode = 0;
    // size_t maxDepth = 17;

    std::unordered_map<CubeState, uint8_t> depths;
    depths[solved] = 0;

    while (!queue.empty()) {
        CubeState current = queue.front();
        queue.pop();

        uint8_t depth = depths[current];
        // if (depth >= maxDepth) continue;

        for (auto move : allowedMoves) {
            CubeState next = current;
            spinManager.applyMove(next, move);
            uint32_t code = encodeG4(next);
            maxcode = std::max(maxcode, code);
            if (seenCodes.count(code) > 0){
                // error("Code already seen: " + std::to_string(code));
                // return ;
            }
            if (seenCodes.insert(code).second) {
                queue.push(next);
                depths[next] = depth + 1;
            }
        }
    }
    std::cout << "Max code: " << maxcode << std::endl;
    std::cout << "Nombre total de codes uniques générés : " << seenCodes.size() << std::endl;
    std::cout << "Taille attendue : " << 663552 << std::endl;
}

int main(int argc, char* argv[]) {
    (void)argc; // Unused parameter
    (void)argv; // Unused parameter
    
    // exploreAllEncodingsG4();

    // std::vector<uint8_t> table;

    // if (pruning::io::load("./table/Thistlethwaite/g4_mirrorSpin.prune", table, 0x01)) {
    //     std::cout << "Table loaded successfully!" << std::endl;
    //     std::cout << "Table size: " << table.size() << std::endl;
    //     return 0;
    // } else {
    //     std::cout << "Failed to load table." << std::endl;
    // }

    
    // CubeState state;
    // SpinManager spinManager;
    // CubeStateHelper helper(state);
    
    // std::cout << encodeG4(state) << std::endl;
    // spinManager.applyMove(state, SpinLst::R2);
    // // spinManager.applyMove(state, SpinLst::D2);
    // // spinManager.applyMove(state, SpinLst::L2);
    // // spinManager.applyMove(state, SpinLst::R2);
    // std::cout << encodeG4(state) << std::endl;

    // std::vector<uint8_t> table;

    // if (pruning::io::load("./table/Thistlethwaite/g4_mirrorSpin.prune", table, 0x01)) {
    //     std::cout << "Table loaded successfully!" << std::endl;
    // } else {
    //     std::cout << "Failed to load table." << std::endl;
    // }

    // std::cout << "table size: " << table.size() << std::endl;   

    // std::cout << "Table content: " << std::endl;
    // for (size_t i = 0; i < table.size(); ++i) {
    //     if (table[i] > 17)
    //         std::cout << "Index " << i << ": " << static_cast<int>(table[i]) << std::endl;
    // }


    if (argc != 2)    
        return error("Usage: " + std::string(argv[0]) + " \" ALL SPIN \" ");

    RubikController controller;

    ParseResult result = controller.parse(argv[1]);
    if (!result.ok) return error("Parsing error: " + result.message);
    controller.applySuffle();
    controller.print();
    controller.solve();
    controller.print();
    return 0;
}

