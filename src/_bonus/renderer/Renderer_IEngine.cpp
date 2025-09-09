#include "renderer/Renderer.hpp"
#include "utils/utils.h"

void Renderer::print() const {return ;};

void Renderer::setSolutionSpins(const std::vector<SpinLst>& solutionSpins) {

    this->_solutionSpinsStr.clear();
    this->_solutionSpins = solutionSpins;
    for (int i = 0; i < static_cast<int>(this->_solutionSpins.size()); i++) {

        this->_rubiksCube.spin(this->_solutionSpins[i], 0.1f);
        if (i)
            this->_solutionSpinsStr += " ";
        this->_solutionSpinsStr += spinToStr(this->_solutionSpins[i]);
    }
};

void Renderer::setSolutionSteps(const std::vector<std::pair<std::string, std::pair<std::vector<SpinLst>,std::vector<SpinLst>>>> \
    & solutionSteps) {

    this->_solutionSteps = solutionSteps;
    this->_currentStep = solutionSteps.size() - 1;
    this->_currentSpin = solutionSteps[this->_currentStep].second.first.size();
};

void Renderer::setShuffleSpins(const std::vector<SpinLst> & shuffleSpins) {

    this->_shuffleSpinsStr.clear();
    this->_shuffleSpins = shuffleSpins;
    for (int i = 0; i < static_cast<int>(this->_shuffleSpins.size()); i++) {

        this->_rubiksCube.spin(this->_shuffleSpins[i], 0.1f);
        if (i)
            this->_shuffleSpinsStr += " ";
        this->_shuffleSpinsStr += spinToStr(this->_shuffleSpins[i]);
    }
};

void Renderer::setTimeExec(const double solveTime) {this->_solveTime = solveTime;};
