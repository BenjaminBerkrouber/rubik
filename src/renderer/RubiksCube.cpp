#include "renderer/RubiksCube.hpp"
#include "renderer/Shader.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

RubiksCube::RubiksCube(const Shader & shader) \
    : _shader(shader), _model(1.0f), _animation(true, true) \
    , _animationSpeed(CUBE_ROTATION_SPEED_DEFAULT, CUBE_SPIN_SPEED_DEFAULT) {}

RubiksCube::~RubiksCube() {}

void RubiksCube::init() {

    this->_cubes.reserve(27);

    for (int x = -1; x <= 1; ++x) {

        for (int y = -1; y <= 1; ++y) {

            for (int z = -1; z <= 1; ++z) {

                this->_cubes.emplace_back(this->_shader);
                this->_cubes.back().mesh.init("cube.glb");
                this->_cubes.back().position = glm::ivec3(x, y, z);
                this->_cubes.back().mesh.translate(this->_cubes.back().position * 2);
            }
        }
    }
}

#include "utils/utils.h"

void RubiksCube::spin(SpinLst spin, const float duration) {

    std::cout << "spin = " << spinToStr(spin) << "\n";

    float angle = 0.0f;
    glm::ivec3 axis(0.0f);
    std::vector<t_cube *> cubes;

    switch (spin) {

        case U:  angle = -glm::half_pi<float>(); axis = {0, 1, 0}; break;
        case U2: angle = -glm::pi<float>();      axis = {0, 1, 0}; break;
        case U3: angle =  glm::half_pi<float>(); axis = {0, 1, 0}; break;

        case D:  angle = -glm::half_pi<float>(); axis = {0,-1, 0}; break;
        case D2: angle = -glm::pi<float>();      axis = {0,-1, 0}; break;
        case D3: angle =  glm::half_pi<float>(); axis = {0,-1, 0}; break;

        case F:  angle = -glm::half_pi<float>(); axis = {0, 0, 1}; break;
        case F2: angle = -glm::pi<float>();      axis = {0, 0, 1}; break;
        case F3: angle =  glm::half_pi<float>(); axis = {0, 0, 1}; break;

        case B:  angle = -glm::half_pi<float>(); axis = {0, 0,-1}; break;
        case B2: angle = -glm::pi<float>();      axis = {0, 0,-1}; break;
        case B3: angle =  glm::half_pi<float>(); axis = {0, 0,-1}; break;

        case L:  angle = -glm::half_pi<float>(); axis = {-1, 0, 0}; break;
        case L2: angle = -glm::pi<float>();      axis = {-1, 0, 0}; break;
        case L3: angle =  glm::half_pi<float>(); axis = {-1, 0, 0}; break;

        case R:  angle = -glm::half_pi<float>(); axis = {1, 0, 0}; break;
        case R2: angle = -glm::pi<float>();      axis = {1, 0, 0}; break;
        case R3: angle =  glm::half_pi<float>(); axis = {1, 0, 0}; break;
    }

    for (t_cube & cube : this->_cubes) {

        if ((axis.x != 0 && cube.position.x == axis.x) \
            || (axis.y != 0 && cube.position.y == axis.y) \
            || (axis.z != 0 && cube.position.z == axis.z)) {

            cube.position = glm::round(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::normalize(glm::vec3(axis))) * glm::vec4(cube.position, 1.0f)));
            cubes.push_back(&cube);
        }
    }

    this->_animations.emplace_back(angle, axis, duration, cubes);
}

void RubiksCube::animate(float deltaTime) {

    if (this->_animation[CUBE_ROTATION_ANIMATION])
        this->rotate(deltaTime * this->_animationSpeed[CUBE_ROTATION_ANIMATION], glm::vec3(0.0f, 1.0f, 0.0f));

    if (this->_animations.empty())
        return ;
    t_animation & animation = this->_animations.front();

    deltaTime *= this->_animationSpeed[CUBE_SPIN_ANIMATION];
    float ratio = deltaTime / animation.duration;

    if (!this->_animation[CUBE_SPIN_ANIMATION] || ratio > 1.0f)
        ratio = 1.0f;

    float deltaAngle = animation.angle * ratio;

    for (t_cube * cube : animation.cubes)
        cube->mesh.rotateAround(deltaAngle, animation.axis, glm::vec3(0.0f));

    animation.duration -= deltaTime;
    animation.angle -= deltaAngle;

    if (animation.duration <= 0.0f)
        this->_animations.erase(this->_animations.begin());
}

void RubiksCube::enableAnimation(const int animation, const bool state) {this->_animation[animation] = state;}

void RubiksCube::setAnimationSpeed(const int animation, const float speed) {this->_animationSpeed[animation] = speed;}

void RubiksCube::translate(const glm::vec3 & offset) {

    this->_model = glm::translate(this->_model, offset);
}

void RubiksCube::rotateAround(const float angle, const glm::vec3 & axis, const glm::vec3 & origin) {

    this->_model = glm::translate(glm::mat4(1.0f), origin) * this->_model;
    this->_model = glm::rotate(glm::mat4(1.0f), angle, axis) * this->_model;
    this->_model = glm::translate(glm::mat4(1.0f), -origin) * this->_model;
}

void RubiksCube::rotate(const float angle, const glm::vec3 & axis) {

    this->_model = glm::rotate(this->_model, angle, axis);
}

void RubiksCube::scale(const glm::vec3 & factor) {

    this->_model = glm::scale(this->_model, factor);
}

void RubiksCube::draw(const glm::mat4 & localModel) const {

    for (const t_cube & cube : this->_cubes)
        cube.mesh.draw(localModel * this->_model);
}
