#pragma once

#include <glm/glm.hpp>

class Renderer;
class Shader;

class Camera {

public:

    Camera(const Renderer & renderer, const Shader & shader);
    ~Camera();

    void init();
    const glm::mat4 getMatrix() const ;

    void orbitAround(const double rotation[2]);
    void zoom(const double delta);

private:

    const Renderer & _renderer;
    const Shader & _shader;

    float _fov;
    float _radius;
    float _yaw;
    float _pitch;
    glm::vec3 _position;

    glm::mat4 _view;
    glm::mat4 _projection;

    void _updatePosition();
    void _updateView();
    void _updateProjection();
};
