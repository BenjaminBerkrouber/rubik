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
            Permutation{0},
            Permutation{1},
            Permutation{2},
            Permutation{3}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{1},
            Permutation{2},
            Permutation{3}
        }
    );
    addSpin(SpinId::U_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{3},
            Permutation{2},
            Permutation{1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{3},
            Permutation{2},
            Permutation{1}
        }
    );
    addSpin(SpinId::U2, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{2},
            Permutation{1},
            Permutation{3}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{2},
            Permutation{1},
            Permutation{3}
        }
    );
    addSpin(SpinId::D, 
        std::array<Permutation, 4>{ 
            Permutation{4},
            Permutation{5},
            Permutation{6},
            Permutation{7}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{8},
            Permutation{9},
            Permutation{10},
            Permutation{11}
        }
    );
    addSpin(SpinId::D_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{4},
            Permutation{7},
            Permutation{6},
            Permutation{5}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{8},
            Permutation{11},
            Permutation{10},
            Permutation{9}
        }
    );
    addSpin(SpinId::D2, 
        std::array<Permutation, 4>{ 
            Permutation{4},
            Permutation{6},
            Permutation{5},
            Permutation{7}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{8},
            Permutation{10},
            Permutation{9},
            Permutation{11}
        }
    );
    addSpin(SpinId::R, 
        std::array<Permutation, 4>{ 
            Permutation{0, 2},
            Permutation{3, 1},
            Permutation{7, 2},
            Permutation{4, 1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{4},
            Permutation{3},
            Permutation{7},
            Permutation{11}
        }
    );
    addSpin(SpinId::R_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{0, 2},
            Permutation{4, 1},
            Permutation{7, 2},
            Permutation{3, 1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{4},
            Permutation{11},
            Permutation{7},
            Permutation{3}
        }
    );
    addSpin(SpinId::R2, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{7},
            Permutation{3},
            Permutation{4}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{4},
            Permutation{7},
            Permutation{3},
            Permutation{11}
        }
    );
    addSpin(SpinId::L, 
        std::array<Permutation, 4>{ 
            Permutation{1, 1},
            Permutation{5, 2},
            Permutation{6, 1},
            Permutation{2, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{1},
            Permutation{5},
            Permutation{9},
            Permutation{6}
        }
    );
    addSpin(SpinId::L_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{1, 1},
            Permutation{2, 2},
            Permutation{6, 1},
            Permutation{5, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{1},
            Permutation{6},
            Permutation{9},
            Permutation{5}
        }
    );
    addSpin(SpinId::L2, 
        std::array<Permutation, 4>{ 
            Permutation{1},
            Permutation{6},
            Permutation{5},
            Permutation{2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{1},
            Permutation{9},
            Permutation{5},
            Permutation{6}
        }
    );
    addSpin(SpinId::F, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1},
            Permutation{4, 2},
            Permutation{5, 1},
            Permutation{1, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1},
            Permutation{4, 1},
            Permutation{8, 1},
            Permutation{5, 1}
        }
    );
    addSpin(SpinId::F_PRIME, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1},
            Permutation{1, 2},
            Permutation{5, 1},
            Permutation{4, 2}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0, 1},
            Permutation{5, 1},
            Permutation{8, 1},
            Permutation{4, 1}
        }
    );
    addSpin(SpinId::F2, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{5},
            Permutation{4},
            Permutation{1}
        }, 
        std::array<Permutation, 4>{ 
            Permutation{0},
            Permutation{8},
            Permutation{4},
            Permutation{5}
        }
    );
    addSpin(SpinId::B, 
        std::array<Permutation, 4>{ 
            Permutation{2, 1},
            Permutation{6, 2},
            Permutation{7, 1},
            Permutation{3, 2}
        },
        std::array<Permutation, 4>{ 
            Permutation{2, 1},
            Permutation{6, 1},
            Permutation{10, 1},
            Permutation{7, 1}
        }
    );
    addSpin(SpinId::B_PRIME, 
        std::array<Permutation, 4>{
            Permutation{2, 1},
            Permutation{3, 2},
            Permutation{7, 1},
            Permutation{6, 2}
    }, 
        std::array<Permutation, 4>{
            Permutation{2, 1},
            Permutation{7, 1},
            Permutation{10, 1},
            Permutation{6, 1}
    }
    );
    addSpin(SpinId::B2, 
        std::array<Permutation, 4>{
            Permutation{2},
            Permutation{7},
            Permutation{6},
            Permutation{3}
    }, 
        std::array<Permutation, 4>{
            Permutation{2},
            Permutation{10},
            Permutation{6},
            Permutation{7}
        }
    );
}


void SpinLib::addSpin(SpinId id, 
        std::array<Permutation, 4> cornersMoves, 
        std::array<Permutation, 4> edgesMoves) 
{
    spins[to_index(id)] = Spin(cornersMoves, edgesMoves);
}
