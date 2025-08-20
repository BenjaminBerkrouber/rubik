#include "renderer/Camera.hpp"
#include "renderer/Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const Renderer & renderer, const Shader & shader) : _renderer(renderer), _shader(shader){}

Camera::~Camera() {}

void Camera::setFov(float fov) {

    this->_fov = fov;
    this->_updateProjection();
}

void Camera::init() {

    this->_fov = 60.0f;
    this->_radius = 45.0f;
    this->_yaw = -0.2f;
    this->_pitch = 0.2f;

    this->_position.x = this->_radius * cos(this->_pitch) * sin(this->_yaw);
    this->_position.y = this->_radius * sin(this->_pitch);
    this->_position.z = this->_radius * cos(this->_pitch) * cos(this->_yaw);

    this->_view = glm::lookAt(this->_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->_projection = glm::perspective(glm::radians(this->_fov), static_cast<float>(this->_renderer.getWindowSize()[WIDTH] / this->_renderer.getWindowSize()[HEIGHT]), 0.1f, 110.0f);
    this->_shader.setMat4(CAMERA, this->_projection * this->_view);
}

void Camera::orbitAround(const double rotation[2]) {

    const double limit = glm::radians(89.0);

    this->_yaw += rotation[X] * 0.002;
    this->_pitch -= rotation[Y] * 0.002;
    if (this->_pitch > limit)
        this->_pitch = limit;
    if (this->_pitch < -limit)
        this->_pitch = -limit;

    this->_updatePosition();
}

void Camera::zoom(const double delta) {

    this->_radius -= delta;
    if (this->_radius < 10.0)
        this->_radius = 10.0;
    if (this->_radius > 100.0)
        this->_radius = 100.0;

    this->_updatePosition();
}

void Camera::_updatePosition() {

    this->_position.x = this->_radius * cos(this->_pitch) * sin(this->_yaw);
    this->_position.y = this->_radius * sin(this->_pitch);
    this->_position.z = this->_radius * cos(this->_pitch) * cos(this->_yaw);

    this->_updateView();
}

void Camera::_updateView() {

    this->_view = glm::lookAt(this->_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->_shader.setMat4(CAMERA, this->_projection * this->_view);
}

void Camera::_updateProjection() {

    this->_projection = glm::perspective(glm::radians(this->_fov), static_cast<float>(this->_renderer.getWindowSize()[WIDTH] / this->_renderer.getWindowSize()[HEIGHT]), 0.1f, 110.0f);
    this->_shader.setMat4(CAMERA, this->_projection * this->_view);
}
