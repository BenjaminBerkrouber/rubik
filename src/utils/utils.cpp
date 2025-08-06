#include "../include/utils/utils.h"

std::string spinToStr(SpinLst spin) {
    switch (spin) {
        case SpinLst::U: return "U";
        case SpinLst::U2: return "U2";
        case SpinLst::U3: return "U'";
        case SpinLst::D: return "D";
        case SpinLst::D2: return "D2";
        case SpinLst::D3: return "D'";
        case SpinLst::F: return "F";
        case SpinLst::F2: return "F2";
        case SpinLst::F3: return "F'";
        case SpinLst::B: return "B";
        case SpinLst::B2: return "B2";
        case SpinLst::B3: return "B'";
        case SpinLst::L: return "L";
        case SpinLst::L2: return "L2";
        case SpinLst::L3: return "L'";
        case SpinLst::R: return "R";
        case SpinLst::R2: return "R2";
        case SpinLst::R3: return "R'";
        default: throw std::invalid_argument("Unknown spin type");
    }
}