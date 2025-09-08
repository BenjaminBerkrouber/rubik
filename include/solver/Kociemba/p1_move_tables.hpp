#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <functional>

#include "../../cube/CubeState.hpp"  
#include "../../spin/SpinManager.hpp" 
#include "../../utils/Constants.hpp"  

struct Counts {
    static constexpr int TWIST  = 2187; 
    static constexpr int FLIP   = 2048; 
    static constexpr int MSLICE = 495;  
    static constexpr int NMOVES = 18; 
    };

class MoveTables {
    public:
        MoveTables() = default;

    
    
    static MoveTables buildOnline(
        const SpinManager& spinMgr,
        std::function<void(CubeState&, uint16_t)> decodeTwist,
        std::function<void(CubeState&, uint16_t)> decodeFlip,
        std::function<void(CubeState&, uint16_t)> decodeMSlice,
        std::function<uint16_t(const CubeState&)> encodeTwist,
        std::function<uint16_t(const CubeState&)> encodeFlip,
        std::function<uint16_t(const CubeState&)> encodeMSlice);

    
    static MoveTables load(const std::string& path);     
        void              save(const std::string& path) const;

    inline uint16_t nextTwist (uint16_t t, int move)  const { return twist_[t*Counts::NMOVES + move]; }
    inline uint16_t nextFlip  (uint16_t f, int move)  const { return  flip_[f*Counts::NMOVES + move]; }
    inline uint16_t nextMSlice(uint16_t s, int move)  const { return mslice_[s*Counts::NMOVES + move]; }

    const std::vector<uint16_t>& rawTwist () const { return twist_;  }
    const std::vector<uint16_t>& rawFlip  () const { return flip_;   }
    const std::vector<uint16_t>& rawMSlice() const { return mslice_; }
    std::vector<uint16_t> twist_;   
    std::vector<uint16_t> flip_;    
    std::vector<uint16_t> mslice_;  

    private:
    
    MoveTables(std::vector<uint16_t> tw, std::vector<uint16_t> fl, std::vector<uint16_t> ms)
        : twist_(std::move(tw)), flip_(std::move(fl)), mslice_(std::move(ms)) {}
};
