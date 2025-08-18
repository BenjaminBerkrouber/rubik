#pragma once


#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "../utils/utils.h"


class IEngine {
    protected:
        CubeState _state;
        
        std::vector<SpinLst> _solutionSpins;
        std::vector<std::pair<std::string, std::vector<SpinLst>>> _solutionSteps;

        std::vector<SpinLst> _shuffleSpins;

    public:
        virtual void print() const = 0;
        virtual ~IEngine() = default;

        void setSolutionSpins(const std::vector<SpinLst>& solutionSpins) {
            // std::cout << "[Engine] Setting solution spins." << std::endl;
            // if (solutionSpins.empty()) {
            //     std::cerr << "[Engine] Warning: Attempted to set empty solution spins." << std::endl;
            //     return;
            // }
            // for (const auto& spin : solutionSpins) {
            //     std::cout << std::left << std::setw(2) << spinToStr(spin) << " ";
            // }
            // std::cout << std::endl;

            _solutionSpins = solutionSpins;
        }

        void setSolutionSteps(const std::vector<std::pair<std::string, std::vector<SpinLst>>>& solutionSteps) {
            _solutionSteps = solutionSteps;

            // std::cout << "[Engine] Setting solution steps." << std::endl;
            // if (solutionSteps.empty()) {
            //     std::cerr << "[Engine] Warning: Attempted to set empty solution steps." << std::endl;
            //     return;
            // }
            // for (const auto& step : solutionSteps) {
            //     std::cout << "[Engine] Step: " << step.first << " - Moves: ";
            //     for (const auto& move : step.second) {
            //         std::cout << std::left << std::setw(2) << spinToStr(move) << " ";
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << std::endl;
        }

        void setShuffleSpins(const std::vector<SpinLst>& shuffleSpins) {
            _shuffleSpins = shuffleSpins;
            // std::cout << "[Engine] Setting shuffle spins." << std::endl;
            // if (shuffleSpins.empty()) {
            //     std::cerr << "[Engine] Warning: Attempted to set empty shuffle spins." << std::endl;
            //     return;
            // }
            // std::cout << "[Engine] Shuffle spins: ";
            // for (const auto& spin : shuffleSpins) {
            //     std::cout << std::left << std::setw(2) << spinToStr(spin) << " ";
            // }
            // std::cout << std::endl;
        }

};