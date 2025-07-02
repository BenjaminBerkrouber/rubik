#include "../include/SpinLib.hpp"

// ================================================================================
// ==== Constructor and Destructor 
// ================================================================================


SpinLib::SpinLib() {
    initializeSpins();
}

SpinLib::~SpinLib() = default;


// ================================================================================
// ==== Getter
// ================================================================================


SpinLib& SpinLib::getInstance() {
    static SpinLib instance;
    return instance;
}

const Spin& SpinLib::getSpin(SpinId id) const {
    size_t index = to_index(id);
    if (index >= spins.size()) throw std::out_of_range("Invalid SpinId");
    return spins[index];
}


// ================================================================================
// ==== Private Methods
// ================================================================================


void SpinLib::initializeSpins() {

    addSpin(SpinId::U, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1},
            Permutation{1, 2},
            Permutation{2, 3},
            Permutation{3, 0}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1},
            Permutation{1, 2},
            Permutation{2, 3},
            Permutation{3, 0}
        }
    );
    addSpin(SpinId::U_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{0, 3},
            Permutation{3, 2},
            Permutation{2, 1},
            Permutation{1, 0}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 3},
            Permutation{3, 2},
            Permutation{2, 1},
            Permutation{1, 0}
        }
    );
    addSpin(SpinId::U2, 
        std::array<Permutation, 4>{ 
            Permutation{0, 2},
            Permutation{1, 3},
            Permutation{2, 0},
            Permutation{3, 1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 2},
            Permutation{1, 3},
            Permutation{2, 0},
            Permutation{3, 1}
        }
    );
    addSpin(SpinId::D, 
        std::array<Permutation, 4>{ 
            Permutation{4, 5},
            Permutation{5, 6},
            Permutation{6, 7},
            Permutation{7, 4}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{8, 9},
            Permutation{9, 10},
            Permutation{10, 11},
            Permutation{11, 8}
        }
    );
    addSpin(SpinId::D_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{4, 7},
            Permutation{7, 6},
            Permutation{6, 5},
            Permutation{5, 4}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{8, 11},
            Permutation{11, 10},
            Permutation{10, 9},
            Permutation{9, 8}
        }
    );
    addSpin(SpinId::D2, 
        std::array<Permutation, 4>{ 
            Permutation{4, 6},
            Permutation{5, 7},
            Permutation{6, 4 },
            Permutation{7, 5}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{8, 10},
            Permutation{9, 11},
            Permutation{10, 8},
            Permutation{11, 9}
        }
    );
    addSpin(SpinId::R, 
        std::array<Permutation, 4>{ 
            Permutation{0, 3, 2},
            Permutation{3, 7, 1},
            Permutation{7, 4, 2},
            Permutation{4, 0, 1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{4, 3},
            Permutation{3, 7},
            Permutation{7, 11},
            Permutation{11, 4}
        }
    );
    addSpin(SpinId::R_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{0, 4, 2},
            Permutation{4, 7, 1},
            Permutation{7, 3, 2},
            Permutation{3, 0, 1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{4, 11},
            Permutation{11, 7},
            Permutation{7, 3},
            Permutation{3, 4}
        }
    );
    addSpin(SpinId::R2, 
        std::array<Permutation, 4>{ 
            Permutation{0, 7},
            Permutation{3, 4},
            Permutation{7, 0},
            Permutation{4, 3}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{4, 7},
            Permutation{3, 11},
            Permutation{7, 4},
            Permutation{11, 3}
        }
    );
    addSpin(SpinId::L, 
        std::array<Permutation, 4>{ 
            Permutation{1, 5, 1},
            Permutation{5, 6, 2},
            Permutation{6, 2, 1},
            Permutation{2, 1, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{1, 5},
            Permutation{5, 9},
            Permutation{9, 6},
            Permutation{6, 1}
        }
    );
    addSpin(SpinId::L_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{1, 2, 1},
            Permutation{2, 6, 2},
            Permutation{6, 5, 1},
            Permutation{5, 1, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{1, 6},
            Permutation{6, 9},
            Permutation{9, 5},
            Permutation{5, 1}
        }
    );
    addSpin(SpinId::L2, 
        std::array<Permutation, 4>{ 
            Permutation{1, 6},
            Permutation{5, 2},
            Permutation{6, 1},
            Permutation{2, 5}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{1, 9},
            Permutation{5, 6},
            Permutation{9, 1},
            Permutation{6, 5}
        }
    );
    addSpin(SpinId::F, 
        std::array<Permutation, 4>{ 
            Permutation{0, 4, 1},
            Permutation{4, 5, 2},
            Permutation{5, 1, 1},
            Permutation{1, 0, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 4, 1},
            Permutation{4, 8, 1},
            Permutation{8, 5, 1},
            Permutation{5, 0, 1}
        }
    );
    addSpin(SpinId::F_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1, 1},
            Permutation{1, 5, 2},
            Permutation{5, 4, 1},
            Permutation{4, 0, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 5, 1},
            Permutation{5, 8, 1},
            Permutation{8, 4, 1},
            Permutation{4, 0, 1}
        }
    );
    addSpin(SpinId::F2, 
        std::array<Permutation, 4>{ 
            Permutation{0, 5},
            Permutation{4, 1},
            Permutation{5, 0},
            Permutation{1, 4}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 8},
            Permutation{4, 5},
            Permutation{8, 0},
            Permutation{5, 4}
        }
    );
    addSpin(SpinId::B, 
        std::array<Permutation, 4>{ 
            Permutation{2, 6, 1},
            Permutation{6, 7, 2},
            Permutation{7, 3, 1},
            Permutation{3, 2, 2}
        },
        std::array<Permutation, 4>{ 
            Permutation{2, 6, 1},
            Permutation{6, 10, 1},
            Permutation{10, 7, 1},
            Permutation{7, 2, 1}
        }
    );
    addSpin(SpinId::B_PRIME, 
        std::array<Permutation, 4>{
            Permutation{2, 3, 1},
            Permutation{3, 7, 2},
            Permutation{7, 6, 1},
            Permutation{6, 2, 2}
    }, 
        std::array<Permutation, 4>{
            Permutation{2, 7, 1},
            Permutation{7, 10, 1},
            Permutation{10, 6, 1},
            Permutation{6, 2, 1}
    }
    );
    addSpin(SpinId::B2, 
        std::array<Permutation, 4>{
            Permutation{2, 7},
            Permutation{6, 3},
            Permutation{7, 2},
            Permutation{3, 6}
    }, 
        std::array<Permutation, 4>{
            Permutation{2, 10},
            Permutation{6, 7},
            Permutation{10, 2},
            Permutation{7, 6}
        }
    );
}


void SpinLib::addSpin(SpinId id, 
        std::array<Permutation, 4> cornersMoves, 
        std::array<Permutation, 4> edgesMoves) 
{
    spins[to_index(id)] = Spin(cornersMoves, edgesMoves);
}
