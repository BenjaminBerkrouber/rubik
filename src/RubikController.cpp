#include "../include/RubikController.hpp"
#include "../include/engine/CubeStateHelper.hpp"
#include "../include/solver/Kociemba/KociembaSolver.hpp"
#include <iomanip>

static inline int error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    return false;
}


RubikController::RubikController()
    :   _parser(),
        _spinManager(),
        _solver(nullptr) {
    _engine = new CubeStateHelper(_cubeState);
    _solver = new KociembaSolver(_cubeState);
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
    return randomSuffle(500);
}

void RubikController::applySuffle() {
    if (_parser.getResults().empty()) {
        error("No moves found in input");
        return;
    }
    std::cout << "Shuffling cube with moves: " << std::endl;
    for (const auto& move : _parser.getResults()) {
        std::cout << std::left << std::setw(2) << spinToStr(move) << " ";
        _spinManager.applyMove(_cubeState, move);
    }
    std::cout << std::endl;
}

void RubikController::print() const {
    _engine->print();
}

void RubikController::solve() {
    if (_solver->solve()) {
        std::cout << "===== End of solving =====" << std::endl;
        std::vector<SpinLst> solution = _solver->getSolution();
        std::cout << "Solution found in " << solution.size() << " moves: " << std::endl;
        for (const SpinLst& move : solution) {
            std::cout << std::left << std::setw(2) << spinToStr(move) << " ";
        }
        std::cout << std::endl << std::endl;
        // _engine->print();
    } else {
        error("Failed to solve the cube");
    }
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