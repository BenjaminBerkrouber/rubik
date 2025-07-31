#pragma once

#include "../cube/CubeState.hpp"
#include "../spin/Spin.hpp"
#include <functional>
#include <vector>
#include <queue>
#include <limits>

class TableGenerator {
public:
    using EncodeFunc = std::function<size_t(const CubeState&)>;

    static std::vector<uint8_t> generate(
        EncodeFunc encodeFn,
        std::function<void(CubeState&, SpinLst)> applyMove,
        size_t tableSize,
        std::vector<SpinLst> allowedMoves = {
            SpinLst::U, SpinLst::U2, SpinLst::U3,
            SpinLst::D, SpinLst::D2, SpinLst::D3,
            SpinLst::L ,SpinLst::L2, SpinLst::L3, 
            SpinLst::R ,SpinLst::R2, SpinLst::R3, 
            SpinLst::F ,SpinLst::F2, SpinLst::F3, 
            SpinLst::B ,SpinLst::B2, SpinLst::B3
        }
    ) {
        std::vector<uint8_t> table(tableSize, std::numeric_limits<uint8_t>::max());
        std::queue<CubeState> queue;

        CubeState solved;
        size_t idx = encodeFn(solved);
        table[idx] = 0;
        queue.push(solved);

        while (!queue.empty()) {
            CubeState current = queue.front();
            queue.pop();

            uint8_t depth = table[encodeFn(current)];

            for (const auto& move : allowedMoves) {
                CubeState next = current;
                applyMove(next, move);
                size_t nextIdx = encodeFn(next);

                if (table[nextIdx] == std::numeric_limits<uint8_t>::max()) {
                    table[nextIdx] = depth + 1;
                    queue.push(next);
                }
            }
        }

        return table;
    }
};
