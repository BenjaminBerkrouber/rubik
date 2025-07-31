#pragma once

class ISolver {
    protected:
        CubeState _state;

    public:
        virtual bool solve() = 0;
        virtual std::vector<SpinLst> getSolution() const = 0;
        virtual ~ISolver() = default;
};