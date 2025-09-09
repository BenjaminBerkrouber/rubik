#pragma once

#include "engine/IEngine.hpp"

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

constexpr int GUI_BUTTON_OFFSET = 5;

constexpr bool VSYNC_DEFAULT = true;
constexpr bool MSAA_DEFAULT = true;

constexpr float GUI_SCALE_DEFAULT = 1.0f;
constexpr float GUI_SCALE_MIN = 0.5f;
constexpr float GUI_SCALE_MAX = 5.0f;

constexpr int SOLVER_KOCIEMBA = 0;
constexpr int SOLVER_PRUNING = 1;

class RubikController;
class Mesh;
class GLFWwindow;

#include <iostream>

class Renderer : public IEngine {

public:

    Renderer();
    ~Renderer();

    void print() const ;
    void setSolutionSpins(const std::vector<SpinLst>& solutionSpins);
    void setSolutionSteps(const std::vector<std::pair<std::string, std::pair<std::vector<SpinLst>,std::vector<SpinLst>>>> \
        & solutionSteps);
    void setShuffleSpins(const std::vector<SpinLst> & shuffleSpins);
    void setTimeExec(const double time);

    const int * getWindowSize() const ;

    bool init(RubikController * controller);
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

    RubikController * _controller;
    struct GLFWwindow * _window;
    const std::string _title;
    int _windowSize[2];
    int _windowPos[2];
    bool _rotatingCam;

    float _time;
    float _deltaTime;
    float _fps;

    int _currentStep;
    int _currentSpin;

    Camera _camera;
    Shader _shader;
    RubiksCube _rubiksCube;

    void _toggleFullscreen();
    void _renderGui();
    void _renderCube();
    void _nextSpin();
    void _prevSpin();

    void _setupImGuiStyle(const int style, const bool rounded);

};
