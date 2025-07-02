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

const Spin& SpinLib::getSpin(const std::string& spinName) const {
    auto it = spins.find(spinName);
    if (it != spins.end()) {
        return it->second;
    }
    throw std::invalid_argument("Spin not found: " + spinName);
}


// ================================================================================
// ==== Private Methods
// ================================================================================


void SpinLib::initializeSpins() {

    spins["U"] = Spin{
        .cornersMoves = { 
            {0, 1}, {1, 2}, {2, 3}, {3, 0} 
        },
        .cornersOrientation = {},
        .edgesMoves = { 
            {0, 1}, {1, 2}, {2, 3}, {3, 0} 
        },
        .edgesOrientation = {}
    };
    spins["U'"] = Spin{
        .cornersMoves = { 
            {0, 3}, {3, 2}, {2, 1}, {1, 0} 
        },
        .cornersOrientation = {},
        .edgesMoves = { 
            {0, 3}, {3, 2}, {2, 1}, {1, 0} 
        },
        .edgesOrientation = {}
    };
    spins["U2"] = Spin{
        .cornersMoves = { 
            {0, 2}, {1, 3}, {2, 0}, {3, 1} 
        },
        .cornersOrientation = {},
        .edgesMoves = { 
            {0, 2}, {1, 3}, {2, 0}, {3, 1} 
        },
        .edgesOrientation = {}
    };


    spins["D"] = Spin{
        .cornersMoves = { 
            {4, 5}, {5, 6}, {6, 7}, {7, 4} 
        },
        .cornersOrientation = {},
        .edgesMoves = { 
            {8, 9}, {9, 10}, {10, 11}, {11, 8} 
        },
        .edgesOrientation = {}
    };
    spins["D'"] = Spin{
        .cornersMoves = { 
            {4, 7}, {7, 6}, {6, 5}, {5, 4} 
        },
        .cornersOrientation = {},
        .edgesMoves = { 
            {8, 11}, {11, 10}, {10, 9}, {9, 8}
        },
        .edgesOrientation = {}
    };
    spins["D2"] = Spin{
        .cornersMoves = { 
            {4, 6}, {5, 7}, {6, 4}, {7, 5} 
        },
        .cornersOrientation = {},
        .edgesMoves = {
            {8, 10}, {9, 11}, {10, 8}, {11, 9}
        },
        .edgesOrientation = {}
    };

    spins["R"] = Spin{
        .cornersMoves = { 
            {0, 3}, {3, 7}, {7, 4}, {4, 0} 
        },
        .cornersOrientation = {
            {0, 1}, {3, 2}, {7, 1}, {4, 2}
        },
        .edgesMoves = {
            {4, 3}, {3, 7}, {7, 11}, {11, 4}
        },
        .edgesOrientation = {}
    };

    spins["R'"] = Spin{
        .cornersMoves = { 
            {0, 4}, {4, 7}, {7, 3}, {3, 0} 
        },
        .cornersOrientation = {
            {4, 2}, {7, 1}, {3, 2}, {0, 1}
        },
        .edgesMoves = {
            {4, 11}, {11, 7}, {7, 3}, {3, 4}
        },
        .edgesOrientation = {}
    };

    spins["R2"] = Spin{
        .cornersMoves = { 
            {0, 7}, {3, 4}, {7, 0}, {4, 3} 
        },
        .cornersOrientation = {},
        .edgesMoves = {
            {4, 7}, {3, 11}, {7, 4}, {11, 3}
        },
        .edgesOrientation = {}
    };

    spins["L"] = Spin{
        .cornersMoves = { 
            {1, 5}, {5, 6}, {6, 2}, {2, 1} 
        },
        .cornersOrientation = {
            {1, 2}, {5, 1}, {6, 2}, {2, 1}
        },
        .edgesMoves = {
            {1, 5}, {5, 9}, {9, 6}, {6, 1}
        },
        .edgesOrientation = {}
    };

    spins["L'"] = Spin{
        .cornersMoves = { 
            {1, 2}, {2, 6}, {6, 5}, {5, 1} 
        },
        .cornersOrientation = {
            {1, 2}, {2, 1}, {6, 2}, {5, 1}
        },
        .edgesMoves = {
            {1, 6}, {6, 9}, {9, 5}, {5, 1}
        },
        .edgesOrientation = {}
    };

    spins["L2"] = Spin{
        .cornersMoves = { 
            {1, 6}, {5, 2}, {6, 1}, {2, 5} 
        },
        .cornersOrientation = {},
        .edgesMoves = {
            {1, 9}, {5, 6}, {9, 1}, {6, 5}
        },
        .edgesOrientation = {}
    };

    spins["F"] = Spin{
        .cornersMoves = { 
            {0, 4}, {4, 5}, {5, 1}, {1, 0} 
        },
        .cornersOrientation = {
            {0, 2}, {4, 1}, {5, 2}, {1, 1}
        },
        .edgesMoves = {
            {0, 4}, {4, 8}, {8, 5}, {5, 0}
        },
        .edgesOrientation = {
            {0, 1}, {4, 1}, {8, 1}, {5, 1}
        }
    };

    spins["F'"] = Spin{
        .cornersMoves = { 
            {0, 1}, {1, 5}, {5, 4}, {4, 0} 
        },
        .cornersOrientation = {
            {0, 2}, {1, 1}, {5, 2}, {4, 1}
        },
        .edgesMoves = {
            {0, 5}, {5, 8}, {8, 4}, {4, 0}
        },
        .edgesOrientation = {
            {0, 1}, {5, 1}, {8, 1}, {4, 1}
        }
    };

    spins["F2"] = Spin{
        .cornersMoves = { 
            {0, 5}, {4, 1}, {5, 0}, {1, 4} 
        },
        .cornersOrientation = {},
        .edgesMoves = {
            {0, 8}, {4, 5}, {8, 0}, {5, 4}
        },
        .edgesOrientation = {}
    };

    spins["B"] = Spin{
        .cornersMoves = { 
            {2, 6}, {6, 7}, {7, 3}, {3, 2} 
        },
        .cornersOrientation = {
            {2, 2}, {6, 1}, {7, 2}, {3, 1}
        },
        .edgesMoves = {
            {2, 6}, {6, 10}, {10, 7}, {7, 2}
        },
        .edgesOrientation = {
            {2, 1}, {6, 1}, {10, 1}, {7, 1}
        }
    };

    spins["B'"] = Spin{
        .cornersMoves = { 
            {2, 3}, {3, 7}, {7, 6}, {6, 2} 
        },
        .cornersOrientation = {
            {2, 2}, {3, 1}, {7, 2}, {6, 1}
        },
        .edgesMoves = {
            {2, 7}, {7, 10}, {10, 6}, {6, 2}
        },
        .edgesOrientation = {
            {2, 1}, {7, 1}, {10, 1}, {6, 1}
        }
    };

    spins["B2"] = Spin{
        .cornersMoves = { 
            {2, 7}, {6, 3}, {7, 2}, {3, 6} 
        },
        .cornersOrientation = {},
        .edgesMoves = {
            {2, 10}, {6, 7}, {10, 2}, {7, 6}
        },
        .edgesOrientation = {}
    };

}
