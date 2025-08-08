#include "renderer/Camera.hpp"
#include "renderer/Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Renderer & renderer) : _renderer(renderer){}

Camera::~Camera() {}

void Camera::init() {

    this->_position = glm::vec3(0.0f, 0.0f, 2.0f);
    this->_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    this->_up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -2.0f));
    this->_projection = glm::perspective(glm::radians(45.0f), (float)(this->_renderer.getWindowSize()[WIDTH] / this->_renderer.getWindowSize()[HEIGHT]), 0.1f, 100.0f);
}

const glm::mat4 Camera::getMatrix() const {return(this->_projection * this->_view);}

void Camera::updateProjection() {

    this->_projection = glm::perspective(glm::radians(45.0f), (float)(this->_renderer.getWindowSize()[WIDTH] / this->_renderer.getWindowSize()[HEIGHT]), 0.1f, 100.0f);
}

// void Camera::orbitAround(glm::vec3 target, const float angle) {

//     this->_view = glm::lookAt();
// }
