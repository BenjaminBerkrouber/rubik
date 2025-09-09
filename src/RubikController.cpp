#include "../include/RubikController.hpp"
#include "../include/engine/CubeStateHelper.hpp"
#include "../include/solver/Kociemba/KociembaSolver.hpp"
#include <iomanip>


// ==============================================================================================================================
// ==== Constructor and Destructor ====
// ==============================================================================================================================


RubikController::RubikController()
    :   _parser(),
        _spinManager() {
    _engine = new CubeStateHelper(_cubeState);
    _solver = new KociembaSolver(_cubeState);
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

void RubikController::generateRandomSpinLst(int count) {
    _parser.clearResults();
    ParseResult result = randomSuffle(count);
    if (!result.ok) {
        error(result.message);
        return;
    }
    _parser.setResults(_parser.getResults());
    applySuffle();
    _engine->setShuffleSpins(getShuffle());
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

bool RubikController::solve(int algorithm) {
    (void)algorithm;
    if (!_solver->solve()) 
        return false;
    std::vector<SpinLst> solution = _solver->getSolution();
    for (const SpinLst& move : solution)
        std::cout << std::left << std::setw(2) << spinToStr(move) << " ";
    std::cout << std::endl;
    return true;
}

void RubikController::reset() {
    _cubeState = CubeState();
    _parser.clearResults();
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
