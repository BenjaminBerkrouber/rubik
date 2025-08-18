#pragma once

#include "Camera.hpp"
#include "Shader.hpp"
#include "RubiksCube.hpp"

#include <string>

constexpr int HEIGHT = 0;
constexpr int WIDTH  = 1;
constexpr int DEFAULT_WIDTH  = 720;
constexpr int DEFAULT_HEIGHT = 480;
constexpr int X = 0;
constexpr int Y = 1;

class Mesh;
class GLFWwindow;

class Renderer {

public:

    Renderer();
    ~Renderer();

    const int * getWindowSize() const ;

    bool init();
    void renderLoop();

    static void staticKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
    static void staticMouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
    static void staticCursorPosCallback(GLFWwindow * window, double xpos, double ypos);
    static void staticScrollCallback(GLFWwindow * window, double xoffset, double yoffset);

    void keyCallback(int key, int scancode, int action, int mods);
    void mouseButtonCallback(int button, int action, int mods);
    void cursorPosCallback(double xpos, double ypos);
    void scrollCallback(double xoffset, double yoffset);

    private:

    struct GLFWwindow* _window;
    const std::string _title;
    int _windowSize[2];
    int _windowPos[2];
    bool _rotatingCam;

    Camera _camera;
    Shader _shader;
    RubiksCube _rubiksCube;

    void _toggleFullscreen();
    // void _renderGui();
    void _renderCube();

};
