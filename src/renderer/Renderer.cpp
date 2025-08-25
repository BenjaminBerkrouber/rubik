#include "renderer/Renderer.hpp"
#include "renderer/Mesh.hpp"
#include "RubikController.hpp"

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

Renderer::Renderer() : _window(nullptr), _title("Rubik"), _camera(*this, this->_shader), _rubiksCube(this->_shader) {

    this->_controller = 0;
    this->_windowSize[WIDTH] = DEFAULT_WIDTH;
    this->_windowSize[HEIGHT] = DEFAULT_HEIGHT;
    this->_windowPos[X] = 0;
    this->_windowPos[Y] = 0;
    this->_rotatingCam = false;
    this->_time = 0.0;
    this->_deltaTime = 0.0;
    this->_fps = 0.0;
    this->_currentStep = 0;
    this->_currentSpin = 0;
}

Renderer::~Renderer() {

    if (ImGui::GetCurrentContext()) {

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    if (this->_window) {

        glfwDestroyWindow(this->_window);
        this->_window = nullptr;
    }
    glfwTerminate();
}

const int * Renderer::getWindowSize() const {return(this->_windowSize);};

bool Renderer::init(RubikController * controller) {

    this->_controller = controller;

    if (!glfwInit()) {

        std::cerr << "GLFW init failed\n";
        return (false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    this->_window = glfwCreateWindow(this->_windowSize[WIDTH], this->_windowSize[HEIGHT], this->_title.c_str(), nullptr, nullptr);
    if (!this->_window) {

        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return (false);
    }

    this->_toggleFullscreen();

    glfwMakeContextCurrent(this->_window);

    glfwSetWindowUserPointer(this->_window, this);
    glfwSetKeyCallback(this->_window, staticKeyCallback);
    glfwSetMouseButtonCallback(this->_window, staticMouseButtonCallback);
    glfwSetCursorPosCallback(this->_window, staticCursorPosCallback);
    glfwSetScrollCallback(this->_window, staticScrollCallback);

    if (!gladLoaderLoadGL()) {

        std::cerr << "Failed to initialize GLAD\n";
        return (false);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    this->_shader.init();
    this->_camera.init();
    this->_rubiksCube.init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(this->_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    Renderer::SetupImGuiStyle();

    return (true);
}

void Renderer::renderLoop() {

    int frameCount = 0;
    float sumDeltaTime = 0.0f;

    while (!glfwWindowShouldClose(this->_window)) {

        const float currentTime = glfwGetTime();

        this->_deltaTime = currentTime - this->_time;
        this->_time = currentTime;

        sumDeltaTime += this->_deltaTime;
        frameCount++;
        if(frameCount >= 30) {

            this->_fps = frameCount / sumDeltaTime;
            sumDeltaTime = 0.0f;
            frameCount = 0;
        }

        glfwGetFramebufferSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);
        glViewport(0, 0, this->_windowSize[WIDTH], this->_windowSize[HEIGHT]);
        glfwPollEvents();

        _renderCube();
        _renderGui();

        glfwSwapBuffers(this->_window);
    }
}

void Renderer::_toggleFullscreen() {

    static bool fullscreen = false;

    if (!this->_window)
        return ;
    fullscreen = !fullscreen;

    if (fullscreen) {

        static GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        static const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwGetWindowPos(this->_window, &this->_windowPos[X], &this->_windowPos[Y]);
        glfwGetWindowSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);
        glfwSetWindowMonitor(this->_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
        glfwSetWindowMonitor(this->_window, nullptr, this->_windowPos[X], this->_windowPos[Y], DEFAULT_WIDTH, DEFAULT_HEIGHT, 0);
}

void Renderer::_renderCube() {

    glClearColor(0.3f, 0.4f, 0.55f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->_rubiksCube.animate(this->_deltaTime);
    this->_rubiksCube.draw();
}

void Renderer::_nextSpin() {

    if (this->_solutionSteps.empty())
        return;

    std::pair<std::string, std::pair<std::vector<SpinLst>, std::vector<SpinLst>>> & step \
        = this->_solutionSteps[this->_currentStep];

    if (this->_currentSpin < static_cast<int>(step.second.first.size())) {

        this->_rubiksCube.spin(step.second.first[this->_currentSpin], 0.2f);
        this->_currentSpin++;
    }
    else if (this->_currentStep + 1 < static_cast<int>(this->_solutionSteps.size())) {

        this->_currentStep++;
        this->_currentSpin = 0;
    }
}

void Renderer::_prevSpin() {

    if (this->_solutionSteps.empty())
        return;
        
    std::pair<std::string, std::pair<std::vector<SpinLst>, std::vector<SpinLst>>> & step \
        = this->_solutionSteps[this->_currentStep];

    if (this->_currentSpin > 0) {

        this->_currentSpin--;
        this->_rubiksCube.spin(step.second.second[this->_currentSpin], 0.2f);
    }
    else if (this->_currentStep > 0) {

        this->_currentStep--;
        this->_currentSpin = static_cast<int>(step.second.second.size()) - 1;
    }
}
