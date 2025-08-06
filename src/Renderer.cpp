#include "Renderer.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {

        Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

        renderer->ToggleFullscreen();
    }
}

Renderer::Renderer() : _window(nullptr), _title("Rubik") {

    _windowSize[WIDTH] = 800;
    _windowSize[HEIGHT] = 600;
    _windowPos[X] = 0;
    _windowPos[Y] = 0;
    this->_fullscreen = false;
}

Renderer::~Renderer() {this->_cleanup();}

bool Renderer::init() {

    if (!glfwInit()) {

        std::cerr << "GLFW init failed\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->_window = glfwCreateWindow(this->_windowSize[WIDTH], this->_windowSize[HEIGHT], this->_title.c_str(), nullptr, nullptr);
    if (!this->_window) {

        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->_window);

    glfwSetWindowUserPointer(this->_window, this);
    glfwSetKeyCallback(this->_window, keyCallback);

    if (!gladLoaderLoadGL()) {

        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    return true;
}

void Renderer::renderLoop() {

    while (!glfwWindowShouldClose(this->_window)) {

        // temp
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }
}

void Renderer::ToggleFullscreen() {

    if (!this->_window)
        return ;
    this->_fullscreen = !this->_fullscreen;

    if (this->_fullscreen) {

        glfwGetWindowPos(this->_window, &this->_windowPos[X], &this->_windowPos[Y]);
        glfwGetWindowSize(this->_window, &this->_windowSize[WIDTH], &this->_windowSize[HEIGHT]);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(this->_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
        glfwSetWindowMonitor(_window, nullptr, this->_windowPos[X], this->_windowPos[Y], this->_windowSize[WIDTH], this->_windowSize[HEIGHT], 0);
}

void Renderer::_cleanup() {

    if (this->_window) {

        glfwDestroyWindow(this->_window);
        this->_window = nullptr;
    }
    glfwTerminate();
}
