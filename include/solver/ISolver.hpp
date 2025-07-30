#pragma once

class ISolver {
    protected:

    public:
        virtual ~ISolver() = 0;
        virtual void print() const = 0;
};