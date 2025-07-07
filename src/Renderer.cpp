#include "Renderer.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

Renderer::Renderer() : _width(800), _height(600), _title("Rubik"), _window(nullptr) {}

Renderer::~Renderer() {this->cleanup();}

bool Renderer::init() {

    if (!glfwInit()) {

        std::cerr << "GLFW init failed\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), nullptr, nullptr);
    if (!this->_window) {

        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->_window);

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

void Renderer::cleanup() {

    if (!this->_window) {

        glfwDestroyWindow(this->_window);
        this->_window = nullptr;
    }
    glfwTerminate();
}
