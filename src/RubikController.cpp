#include "../include/RubikController.hpp"
#include "../include/engine/CubeStateHelper.hpp"
#include "../include/solver/Kociemba/KociembaSolver.hpp"
#include "../include/solver/Thistlethwaite/ThistlethwaiteSolver.hpp"
#include <iomanip>


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


RubikController::RubikController()
    :   _parser(),
        _spinManager(),
        _solver(nullptr) {
    _engine = new CubeStateHelper(_cubeState);
    // _solver = new KociembaSolver(_cubeState);
    _solver = new ThistlethwaiteSolver(_cubeState);
}

RubikController::~RubikController() {
    if (_solver) {
        delete _solver;
        _solver = nullptr;
    }
    if (_engine) {
        delete _engine;
        _engine = nullptr;
    }
}


// =============================================================================================================================
// ==== Utils Methods ====
// =============================================================================================================================


static inline int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return false;
}



// ==============================================================================================================================
// ==== Public Methods ====
// ==============================================================================================================================


ParseResult RubikController::parse(const std::string& input) {
    return SHUFFLE_MODE ? _parser.parse(input) : randomSuffle(500);
}

void RubikController::applySuffle() {
    if (_parser.getResults().empty()) {
        error("No moves found in input");
        return;
    }
    for (const auto& move : _parser.getResults())
        _spinManager.applyMove(_cubeState, move);
}

void RubikController::print() const {
    _engine->print();
}

void RubikController::solve() {
    if (!_solver->solve()) 
        return;
    // std::vector<SpinLst> solution = _solver->getSolution();
    // for (const SpinLst& move : solution)
    //     std::cout << std::left << std::setw(2) << spinToStr(move) << " ";
    // std::cout << std::endl;
}

void RubikController::reset() {
    _cubeState = CubeState();
    _parser.clearResults();
    if (_solver) {
        delete _solver;
        _solver = nullptr;
    }
    if (_engine) {
        delete _engine;
        _engine = nullptr;
    }
    _engine = new CubeStateHelper(_cubeState);
}


// =============================================================================================================================
// ==== Getters ====
// =============================================================================================================================


std::vector<SpinLst> RubikController::getShuffle() const {
    return _parser.getResults();
}

std::vector<SpinLst> RubikController::getSolution() const {
    return _solver->getSolution();
}  


// ==============================================================================================================================
// ==== Private Methods ====
// ==============================================================================================================================


ParseResult RubikController::randomSuffle(int count) {
    if (count <= 0) return ParseResult{false, "Count must be greater than 0"};
    _parser.clearResults();
    std::vector<SpinLst> spins = _parser.generateRandomSpinLst(count);
    if (spins.empty()) return ParseResult{false, "No moves generated"};
    _parser.setResults(spins);
    return ParseResult{true, "Random shuffle generated with " + std::to_string(count) + " moves"};
}
