#pragma once

#include "renderer/Mesh.hpp"
#include "spin/Spin.hpp"

#include <vector>

class Shader;

struct t_cube {

    Mesh mesh;
    glm::vec3 position;

    t_cube(const Shader & shader) : mesh(shader) {}
};

class RubiksCube {

public:

    RubiksCube(const Shader & shader);
    ~RubiksCube();

    void init();
    void spin(SpinLst spin);
    void draw() const;

private:

    const Shader & _shader;

    std::vector<t_cube> _cubes;

};
