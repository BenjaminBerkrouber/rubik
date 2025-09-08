#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <functional>

#include "../../cube/CubeState.hpp"
#include "../../spin/SpinManager.hpp"
#include "../../utils/Constants.hpp"

struct P2Counts {
    static constexpr int CORNER = 40320;
    static constexpr int MSLICE = 24;   
    static constexpr int UDSLICE= 40320;
};

class P2MoveTables {
public:
    P2MoveTables() = default;

    static P2MoveTables buildOnline(
        SpinManager& spinMgr,
        const std::vector<SpinLst>& allowedMoves,
        std::function<void(CubeState&, uint32_t)> decodeCorner,
        std::function<void(CubeState&, uint32_t)> decodeMSlicePerm,
        std::function<void(CubeState&, uint32_t)> decodeUDSlicePerm,
        std::function<uint16_t(const CubeState&)> encodeCorner,
        std::function<uint16_t(const CubeState&)> encodeMSlicePerm,
        std::function<uint16_t(const CubeState&)> encodeUDSlicePerm
    );

    
    static P2MoveTables load(const std::string& path);
    void save(const std::string& path) const;

    
    inline uint16_t nextCorner (uint16_t idx, int mv) const { return corner_[idx*nmoves_ + mv]; }
    inline uint16_t nextMSlice (uint16_t idx, int mv) const { return mslice_[idx*nmoves_ + mv]; }
    inline uint16_t nextUDSlice(uint16_t idx, int mv) const { return udslc_ [idx*nmoves_ + mv]; }

    inline int nmoves() const { return nmoves_; }

    private:
    int nmoves_ = 0;
    std::vector<uint16_t> corner_;
    std::vector<uint16_t> mslice_;
    std::vector<uint16_t> udslc_; 

    P2MoveTables(int nm,
                std::vector<uint16_t> c,
                std::vector<uint16_t> m,
                std::vector<uint16_t> u)
        : nmoves_(nm), corner_(std::move(c)), mslice_(std::move(m)), udslc_(std::move(u)) {}
};
