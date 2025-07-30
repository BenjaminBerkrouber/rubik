#pragma once

class IEngine {
    protected:
        CubeState _state;

    public:
        virtual void print() const = 0;
        virtual ~IEngine() = default;
};