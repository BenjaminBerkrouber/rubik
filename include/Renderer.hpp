#pragma once

#include <string>

#define HEIGHT  0
#define WIDTH   1
#define X       0
#define Y       1

class Renderer {

public:

    Renderer();
    ~Renderer();

    bool init();
    void renderLoop();
    void ToggleFullscreen();

private:

    struct GLFWwindow* _window;
    const std::string _title;
    int _windowSize[2];
    int _windowPos[2];
    bool _fullscreen;

    void _cleanup();

};
