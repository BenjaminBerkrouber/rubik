#include "renderer/Renderer.hpp"

#include <GLFW/glfw3.h>

void Renderer::staticKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {

    static Renderer * renderer = static_cast<Renderer * >(glfwGetWindowUserPointer(window));

    renderer->keyCallback(key, scancode, action, mods);
};

void Renderer::keyCallback(int key, int scancode, int action, int mods) {

    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(this->_window, true);
    else if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
        this->_toggleFullscreen();
}

void Renderer::staticMouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {

    static Renderer * renderer = static_cast<Renderer * >(glfwGetWindowUserPointer(window));

    renderer->mouseButtonCallback(button, action, mods);
}

void Renderer::mouseButtonCallback(int button, int action, int mods) {

    (void)mods;
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {

        if (action == GLFW_PRESS) {

            this->_rotatingCam = true;
            glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            // this->_rubiksCube.enableAnimation(CUBE_ROTATION_ANIMATION, false);
        }
        else {

            this->_rotatingCam = false;
            glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // this->_rubiksCube.enableAnimation(CUBE_ROTATION_ANIMATION, true);
        }
    }
}

void Renderer::staticCursorPosCallback(GLFWwindow * window, double xpos, double ypos) {

    Renderer * renderer = static_cast<Renderer * >(glfwGetWindowUserPointer(window));

    renderer->cursorPosCallback(xpos, ypos);
}

void Renderer::cursorPosCallback(double xpos, double ypos) {

    static double lastMousePos[2];

    if (this->_rotatingCam) {

        double rotation[2];

        glfwGetCursorPos(this->_window, &xpos, &ypos);

        rotation[X] = lastMousePos[X] - xpos;
        rotation[Y] = lastMousePos[Y] - ypos;

        this->_camera.orbitAround(rotation);
    }
    lastMousePos[X] = xpos;
    lastMousePos[Y] = ypos;
}

void Renderer::staticScrollCallback(GLFWwindow * window, double xoffset, double yoffset) {

    Renderer * renderer = static_cast<Renderer * >(glfwGetWindowUserPointer(window));

    renderer->scrollCallback(xoffset, yoffset);
}

void Renderer::scrollCallback(double xoffset, double yoffset) {

    (void)xoffset;
    this->_camera.zoom(yoffset);
}
