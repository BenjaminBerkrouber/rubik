#pragma once

class IEngine {
    protected:
        CubeState _state;
        std::vector<SpinLst> _solutionSpins;
        std::vector<<std::pair<std::string, std::vector<SpinLst>> _solutionSteps;

    public:
        virtual void print() const = 0;
        virtual ~IEngine() = default;
        
        void setSolutionSpins(const std::vector<SpinLst>& solutionSpins) {
            _solutionSpins = solutionSpins;
        }

        void setSolutionSteps(const std::vector<std::pair<std::string, std::vector<SpinLst>>>& solutionSteps) {
            _solutionSteps = solutionSteps;
        }

};