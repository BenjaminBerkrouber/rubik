
#include <stdexcept>
#include <cstdio>
#include <algorithm>
#include "../../../include/solver/Kociemba/p1_move_tables.hpp"

static inline void setEdgeId(CubeState& s, int pos, uint8_t id) {
    s.edges &= ~(0xFULL << (pos*4));
    s.edges |= (uint64_t(id) & 0xFULL) << (pos*4);
}

static inline CubeState identityCube() {
    CubeState s{};
    
    for (int p = 0; p < 12; ++p) setEdgeId(s, p, (uint8_t)p);
    return s;
}

static inline void clearOrientBits(CubeState& s) {
    s.corners &= ~((~0ULL) << 32);
    s.edges   &= ((1ULL << 48) - 1);
}


static int binom(int n, int k) {
    if (k<0 || k>n) return 0;
    if (k==0 || k==n) return 1;
    long long r = 1;
    for (int i=1;i<=k;++i) r = r*(n-k+i)/i;
    return int(r);
}

static std::array<uint8_t,4> unrankMSlice(uint16_t code) {
    int idx = 494 - code;
    std::array<uint8_t,4> pos{};
    int x = 11;
    for (int k = 4; k >= 1; --k) {
        while (binom(x, k) > idx) --x;
        pos[k-1] = (uint8_t)x;
        idx -= binom(x, k);
        --x;
    }
    std::sort(pos.begin(), pos.end());
    return pos;
}


MoveTables MoveTables::buildOnline(
    const SpinManager& spinMgr,
    std::function<void(CubeState&, uint16_t)> decodeTwist,
    std::function<void(CubeState&, uint16_t)> decodeFlip,
    std::function<void(CubeState&, uint16_t)> decodeMSlice,
    std::function<uint16_t(const CubeState&)> encodeTwist,
    std::function<uint16_t(const CubeState&)> encodeFlip,
    std::function<uint16_t(const CubeState&)> encodeMSlice)
    {
        (void)decodeTwist; (void)decodeFlip; (void)decodeMSlice;
        (void)encodeTwist; (void)encodeFlip; (void)encodeMSlice;
    const int NM = Counts::NMOVES;

    std::vector<uint16_t> T(Counts::TWIST  * NM);
    std::vector<uint16_t> F(Counts::FLIP   * NM);
    std::vector<uint16_t> S(Counts::MSLICE * NM);

    
    for (int t = 0; t < Counts::TWIST; ++t) {
        CubeState cs = identityCube();
        clearOrientBits(cs);
        decodeTwist(cs, (uint16_t)t);
        for (int m = 0; m < NM; ++m) {
        CubeState tmp = cs;
        const auto mv = static_cast<SpinLst>(m);
        
        const_cast<SpinManager&>(spinMgr).applyMove(tmp, mv);
        T[t*NM + m] = encodeTwist(tmp);
        }
    }

    
    for (int f = 0; f < Counts::FLIP; ++f) {
        CubeState cs = identityCube();
        clearOrientBits(cs);
        decodeFlip(cs, (uint16_t)f);
        for (int m = 0; m < NM; ++m) {
        CubeState tmp = cs;
        const auto mv = static_cast<SpinLst>(m);
        const_cast<SpinManager&>(spinMgr).applyMove(tmp, mv);
        F[f*NM + m] = encodeFlip(tmp);
        }
    }

    
    for (int s = 0; s < Counts::MSLICE; ++s) {
        CubeState cs = identityCube();

        
        auto pos = unrankMSlice((uint16_t)s); 
        std::array<bool,12> isSlice{};
        for (auto p : pos) isSlice[p] = true;

        uint8_t nextNonSlice = 0;
        for (int p = 0; p < 12; ++p) {
        if (!isSlice[p]) setEdgeId(cs, p, nextNonSlice++); 
        }
        for (int i = 0; i < 4; ++i) setEdgeId(cs, pos[i], 8 + i); 

        for (int m = 0; m < NM; ++m) {
        CubeState tmp = cs;
        const auto mv = static_cast<SpinLst>(m);
        const_cast<SpinManager&>(spinMgr).applyMove(tmp, mv);
        S[s*NM + m] = encodeMSlice(tmp);
        }
    }

    return MoveTables(std::move(T), std::move(F), std::move(S));
}


static constexpr uint32_t MAGIC = 0x31544D50; 
static constexpr uint32_t VERSION = 1;

void MoveTables::save(const std::string& path) const {
    if (twist_.size()  != size_t(Counts::TWIST  * Counts::NMOVES) ||
        flip_.size()   != size_t(Counts::FLIP   * Counts::NMOVES) ||
        mslice_.size() != size_t(Counts::MSLICE * Counts::NMOVES))
        throw std::runtime_error("MoveTables::save: invalid sizes");

    FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) throw std::runtime_error("MoveTables::save: open failed");

    uint32_t hdr[6] = {
        MAGIC, VERSION,
        (uint32_t)Counts::NMOVES,
        (uint32_t)Counts::TWIST,
        (uint32_t)Counts::FLIP,
        (uint32_t)Counts::MSLICE
    };
    std::fwrite(hdr, sizeof(hdr), 1, f);

    std::fwrite(twist_.data(),  sizeof(uint16_t), twist_.size(),  f);
    std::fwrite(flip_.data(),   sizeof(uint16_t), flip_.size(),   f);
    std::fwrite(mslice_.data(), sizeof(uint16_t), mslice_.size(), f);
    std::fclose(f);
}

MoveTables MoveTables::load(const std::string& path) {
    try {
        FILE* f = std::fopen(path.c_str(), "rb");
        if (!f) throw std::runtime_error("MoveTables::load: open failed");
    
        uint32_t hdr[6]{};
        if (std::fread(hdr, sizeof(hdr), 1, f) != 1) {
            std::fclose(f); throw std::runtime_error("MoveTables::load: header read failed");
        }
        if (hdr[0] != MAGIC || hdr[1] != VERSION) {
            std::fclose(f); throw std::runtime_error("MoveTables::load: bad magic/version");
        }
        if (int(hdr[2]) != Counts::NMOVES ||
            int(hdr[3]) != Counts::TWIST ||
            int(hdr[4]) != Counts::FLIP  ||
            int(hdr[5]) != Counts::MSLICE) {
            std::fclose(f); throw std::runtime_error("MoveTables::load: shape mismatch");
        }
    
        std::vector<uint16_t> T(Counts::TWIST  * Counts::NMOVES);
        std::vector<uint16_t> F(Counts::FLIP   * Counts::NMOVES);
        std::vector<uint16_t> S(Counts::MSLICE * Counts::NMOVES);
    
        if (std::fread(T.data(), sizeof(uint16_t), T.size(), f) != T.size() ||
            std::fread(F.data(), sizeof(uint16_t), F.size(), f) != F.size() ||
            std::fread(S.data(), sizeof(uint16_t), S.size(), f) != S.size()) {
            std::fclose(f); throw std::runtime_error("MoveTables::load: payload read failed");
        }
        std::fclose(f);
        return MoveTables(std::move(T), std::move(F), std::move(S));
    } catch (const std::exception& e) {
        (void)e;
        return MoveTables();
    }
}

