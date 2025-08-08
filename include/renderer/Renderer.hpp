#pragma once

#include <string>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

constexpr int HEIGHT = 0;
constexpr int WIDTH  = 1;
constexpr int DEFAULT_WIDTH  = 720;
constexpr int DEFAULT_HEIGHT = 517;
constexpr int X = 0;
constexpr int Y = 1;

class Renderer {

public:

    Renderer();
    ~Renderer();

    bool init();
    void renderLoop();
    void toggleFullscreen();
    const int * getWindowSize() const ;

    void objectRenderer(const std::string );

private:

    struct GLFWwindow* _window;
    const std::string _title;
    int _windowSize[2];
    int _windowPos[2];
    bool _fullscreen;

    Camera _camera;
    Shader _shader;
    Mesh _mesh;

    // void _renderGui();
    void _renderCube();
    void _cleanup();
};
