#include "../../../include/solver/Kociemba/p2_move_tables.hpp"
#include <stdexcept>
#include <cstdio>
#include <algorithm>
#include <array>

static inline void setEdgeId(CubeState& s, int pos, uint8_t id) {
    s.edges &= ~(0xFULL << (pos*4));
    s.edges |= (uint64_t(id) & 0xFULL) << (pos*4);
}
static inline void setCornerId(CubeState& s, int pos, uint8_t id) {
    s.corners &= ~(0xFULL << (pos*4));
    s.corners |= (uint64_t(id) & 0xFULL) << (pos*4);
}

static CubeState identityCube() {
    CubeState s{};
    for (int p = 0; p < 12; ++p) setEdgeId(s, p, (uint8_t)p);
    for (int p = 0; p < 8;  ++p) setCornerId(s, p, (uint8_t)p);
    return s;
}

P2MoveTables P2MoveTables::buildOnline(
    SpinManager& spinMgr,
    const std::vector<SpinLst>& moves,
    std::function<void(CubeState&, uint32_t)> decodeCorner,
    std::function<void(CubeState&, uint32_t)> decodeMSlicePerm,
    std::function<void(CubeState&, uint32_t)> decodeUDSlicePerm,
    std::function<uint16_t(const CubeState&)> encodeCorner,
    std::function<uint16_t(const CubeState&)> encodeMSlicePerm,
    std::function<uint16_t(const CubeState&)> encodeUDSlicePerm)
{
    const int NM = (int)moves.size();
    if (NM <= 0) throw std::runtime_error("P2MoveTables: moves empty");

    std::vector<uint16_t> C(P2Counts::CORNER * NM);
    std::vector<uint16_t> M(P2Counts::MSLICE * NM);
    std::vector<uint16_t> U(P2Counts::UDSLICE* NM);

    for (int idx = 0; idx < P2Counts::CORNER; ++idx) {
        CubeState cs = identityCube();
        decodeCorner(cs, (uint32_t)idx);
        for (int m = 0; m < NM; ++m) {
        CubeState tmp = cs;
        spinMgr.applyMove(tmp, moves[m]);
        C[idx*NM + m] = encodeCorner(tmp);
        }
    }

    for (int idx = 0; idx < P2Counts::MSLICE; ++idx) {
        CubeState cs = identityCube();
        decodeMSlicePerm(cs, (uint32_t)idx);
        for (int m = 0; m < NM; ++m) {
        CubeState tmp = cs;
        spinMgr.applyMove(tmp, moves[m]);
        M[idx*NM + m] = encodeMSlicePerm(tmp);
        }
    }

    for (int idx = 0; idx < P2Counts::UDSLICE; ++idx) {
        CubeState cs = identityCube();
        decodeUDSlicePerm(cs, (uint32_t)idx);
        for (int m = 0; m < NM; ++m) {
        CubeState tmp = cs;
        spinMgr.applyMove(tmp, moves[m]);
        U[idx*NM + m] = encodeUDSlicePerm(tmp);
        }
    }

    return P2MoveTables(NM, std::move(C), std::move(M), std::move(U));
}

static constexpr uint32_t MAGIC = 0x5032544D;
static constexpr uint32_t VERSION = 1;

void P2MoveTables::save(const std::string& path) const {
    if (nmoves_ <= 0) throw std::runtime_error("P2MoveTables::save: nmoves invalid");
    FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) throw std::runtime_error("P2MoveTables::save: open failed");

    uint32_t hdr[6] = {
        MAGIC, VERSION,
        (uint32_t)nmoves_,
        (uint32_t)P2Counts::CORNER,
        (uint32_t)P2Counts::MSLICE,
        (uint32_t)P2Counts::UDSLICE
    };
    std::fwrite(hdr, sizeof(hdr), 1, f);
    std::fwrite(corner_.data(), sizeof(uint16_t), corner_.size(), f);
    std::fwrite(mslice_.data(), sizeof(uint16_t), mslice_.size(), f);
    std::fwrite(udslc_.data(),  sizeof(uint16_t), udslc_.size(),  f);
    std::fclose(f);
}

P2MoveTables P2MoveTables::load(const std::string& path) {
    FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) throw std::runtime_error("P2MoveTables::load: open failed");

    uint32_t hdr[6]{};
    if (std::fread(hdr, sizeof(hdr), 1, f) != 1) {
        std::fclose(f); throw std::runtime_error("P2MoveTables::load: header read failed");
    }
    if (hdr[0] != MAGIC || hdr[1] != VERSION) {
        std::fclose(f); throw std::runtime_error("P2MoveTables::load: bad magic/version");
    }
    int nm = (int)hdr[2];
    if (nm <= 0) { std::fclose(f); throw std::runtime_error("P2MoveTables::load: bad nmoves"); }

    const int C = (int)hdr[3], M = (int)hdr[4], U = (int)hdr[5];
    if (C != P2Counts::CORNER || M != P2Counts::MSLICE || U != P2Counts::UDSLICE) {
        std::fclose(f); throw std::runtime_error("P2MoveTables::load: shape mismatch");
    }

    std::vector<uint16_t> c(C * nm), m(M * nm), u(U * nm);
    if (std::fread(c.data(), sizeof(uint16_t), c.size(), f) != c.size() ||
        std::fread(m.data(), sizeof(uint16_t), m.size(), f) != m.size() ||
        std::fread(u.data(), sizeof(uint16_t), u.size(), f) != u.size()) {
        std::fclose(f); throw std::runtime_error("P2MoveTables::load: payload read failed");
    }
    std::fclose(f);
    return P2MoveTables(nm, std::move(c), std::move(m), std::move(u));
}
