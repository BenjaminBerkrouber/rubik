#pragma once

#include <vector>
#include <string>
#include "spin/Spin.hpp"

class IEngine {

    protected:

        std::vector<SpinLst> _solutionSpins;

        /**
            vector of pairs where each pair contains:
            - a string representing the step name (e.g., "Cross", "F2L", "OLL", "PLL")
            - a pair of vectors:
                - first vector contains the spins for that step
                - second vector contains the inverse spins for that step
            
        */
        std::vector<std::pair<std::string, std::pair<std::vector<SpinLst>,std::vector<SpinLst>>>> _solutionSteps;

        std::vector<SpinLst> _shuffleSpins;

        std::string _shuffleSpinsStr;
        std::string _solutionSpinsStr;

        double _solveTime;

    public:

        virtual void print() const = 0;
        virtual ~IEngine() = default;

        virtual void setSolutionSpins(const std::vector<SpinLst>& solutionSpins) = 0;
        virtual void setSolutionSteps(const std::vector<std::pair<std::string, std::pair<std::vector<SpinLst>,std::vector<SpinLst>>>>& solutionSteps) = 0;
        virtual void setShuffleSpins(const std::vector<SpinLst>& shuffleSpins) = 0;
        virtual void setTimeExec(const double time) = 0;

};
