#pragma once

#include "renderer/Mesh.hpp"
#include "spin/Spin.hpp"

#include <vector>

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

    void init();
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
};
