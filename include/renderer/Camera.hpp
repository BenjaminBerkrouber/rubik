#pragma once

#include <glm/glm.hpp>

constexpr float SPEED = 0.1f;
constexpr float SENSITIVITY  = 100.0f;

class Renderer;

class Camera {

public:

    Camera(const Renderer & renderer);
    ~Camera();

    void init();
    const glm::mat4 getMatrix() const ;

    void updateProjection() ;

    // void orbitAround(glm::vec3 target, const float speed);

private:

    const Renderer & _renderer;
    glm::vec3 _position;
    glm::vec3 _orientation;
    glm::vec3 _up;

    glm::mat4 _view;
    glm::mat4 _projection;
};
