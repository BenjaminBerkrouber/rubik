#pragma once

#include "renderer/Mesh.hpp"
#include "spin/Spin.hpp"

#include <vector>

constexpr bool CUBE_ROTATION_ANIMATION_DEFAULT = true;
constexpr bool CUBE_SPIN_ANIMATION_DEFAULT = true;

constexpr int CUBE_ROTATION_ANIMATION = 0;
constexpr float CUBE_ROTATION_SPEED_DEFAULT = 0.5f;
constexpr float CUBE_ROTATION_SPEED_MIN = 0.1f;
constexpr float CUBE_ROTATION_SPEED_MAX = 5.0f;

constexpr int CUBE_SPIN_ANIMATION = 1;
constexpr float CUBE_SPIN_SPEED_DEFAULT = 1.0f;
constexpr float CUBE_SPIN_SPEED_MIN = 0.1f;
constexpr float CUBE_SPIN_SPEED_MAX = 5.0f;

class Shader;

struct t_cube {

    Mesh mesh;
    glm::ivec3 position;

    t_cube(const Shader & shader) : mesh(shader) {};
};

struct t_animation {

    float angle;
    float duration;
    glm::ivec3 axis;

    std::vector<t_cube *> cubes;

    bool active = false;

    t_animation(const float angle, const glm::ivec3 axis, const float duration, std::vector<t_cube *> cubes) \
        : angle(angle), duration(duration), axis(axis), cubes(cubes) {};
};

class RubiksCube {

public:

    RubiksCube(const Shader & shader);
    ~RubiksCube();

    void setAnimationState(const int animation, const bool state);
    void setAnimationSpeed(const int animation, const float speed);

    bool getAnimationState(const int animation);

    void init();
    void resetPos();

    void spin(SpinLst spin, const float duration = 1.0f);
    void animate(const float deltaTime);

    void translate(const glm::vec3 & offset);
    void rotate(const float angle, const glm::vec3 & axis);
    void rotateAround(const float angle, const glm::vec3 & axis, const glm::vec3 & origin);
    void scale(const glm::vec3 & factor);

    void draw(const glm::mat4 & localModel = glm::mat4(1.0f)) const;

private:

    const Shader & _shader;

    glm::mat4 _model;

    std::vector<t_cube> _cubes;

    std::vector<t_animation> _animations;

    bool _animation[2];
    float _animationSpeed[2];
};
