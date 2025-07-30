#include "../include/RubikController.hpp"
#include "../include/engine/CubeStateHelper.hpp"

static inline int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return false;
}


RubikController::RubikController()
    :   _parser(),
        _spinManager(),
        _solver(nullptr) {
    _engine = new CubeStateHelper(_cubeState);
    _solver = nullptr;
}

bool RubikController::parseInput(const std::string& input) {
    ParseResult parsed = _parser.parse(input);
    if (!parsed.ok) return error(std::string(parsed.message));
    return true;
}

bool RubikController::randomSuffle(int count) {
    if (count <= 0) return error("Count must be greater than 0");
    _parser.clearResults();
    std::vector<SpinLst> spins = _parser.generateRandomSpinLst(count);
    _parser.setResults(spins);
    return true;
}

bool RubikController::parse(const std::string& input) {
    if (SHUFFLE_MODE) return parseInput(input);
    return randomSuffle(5000000);
}

void RubikController::applySuffle() {
    if (_parser.getResults().empty()) {
        error("No moves found in input");
        return;
    }
    for (const auto& move : _parser.getResults()) {
        _spinManager.applyMove(_cubeState, move);
    }
}

void RubikController::print() const {
    _engine->print();
}

void RubikController::solve() {

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