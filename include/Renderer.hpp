#pragma once

#include <string>

class Renderer {

public:

    Renderer();
    ~Renderer();

    bool init();
    void renderLoop();

private:

    int _width;
    int _height;
    const std::string _title;
    struct GLFWwindow* _window;

    void cleanup();

};
