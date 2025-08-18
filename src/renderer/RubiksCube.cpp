#include "renderer/RubiksCube.hpp"
#include "renderer/Shader.hpp"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

RubiksCube::RubiksCube(const Shader & shader) : _shader(shader) {}

RubiksCube::~RubiksCube() {}

void RubiksCube::init() {

    this->_cubes.reserve(27);

    for (int x = -1; x <= 1; ++x) {

        for (int y = -1; y <= 1; ++y) {

            for (int z = -1; z <= 1; ++z) {

                this->_cubes.emplace_back(this->_shader);
                this->_cubes.back().mesh.init("cube.glb");
                this->_cubes.back().position = glm::vec3(x, y, z);
                this->_cubes.back().mesh.translate(this->_cubes.back().position * 2.0f);
            }
        }
    }
}

void RubiksCube::spin(SpinLst spin) {

    float angle = 0.0f;
    glm::vec3 axis(0.0f);

    switch (spin) {

        case U:  angle = -glm::half_pi<float>(); axis = {0, 1, 0}; break;
        case U2: angle = -glm::pi<float>();      axis = {0, 1, 0}; break;
        case U3: angle =  glm::half_pi<float>(); axis = {0, 1, 0}; break;

        case D:  angle =  glm::half_pi<float>(); axis = {0,-1, 0}; break;
        case D2: angle =  glm::pi<float>();      axis = {0,-1, 0}; break;
        case D3: angle = -glm::half_pi<float>(); axis = {0,-1, 0}; break;

        case F:  angle = -glm::half_pi<float>(); axis = {0, 0, 1}; break;
        case F2: angle = -glm::pi<float>();      axis = {0, 0, 1}; break;
        case F3: angle =  glm::half_pi<float>(); axis = {0, 0, 1}; break;

        case B:  angle =  glm::half_pi<float>(); axis = {0, 0,-1}; break;
        case B2: angle =  glm::pi<float>();      axis = {0, 0,-1}; break;
        case B3: angle = -glm::half_pi<float>(); axis = {0, 0,-1}; break;

        case L:  angle = -glm::half_pi<float>(); axis = {1, 0, 0}; break;
        case L2: angle = -glm::pi<float>();      axis = {1, 0, 0}; break;
        case L3: angle =  glm::half_pi<float>(); axis = {1, 0, 0}; break;

        case R:  angle =  glm::half_pi<float>(); axis = {-1, 0, 0}; break;
        case R2: angle =  glm::pi<float>();      axis = {-1, 0, 0}; break;
        case R3: angle = -glm::half_pi<float>(); axis = {-1, 0, 0}; break;
    }

    for (t_cube & cube : this->_cubes) {

        if ((axis.x != 0 && glm::round(cube.position.x) == axis.x) \
        || (axis.y != 0 && glm::round(cube.position.y) == axis.y) \
        || (axis.z != 0 && glm::round(cube.position.z) == axis.z)) {

            cube.mesh.rotate(angle, glm::normalize(axis));
            cube.position = glm::round(glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis)) * glm::vec4(cube.position, 1.0f)));
        }
    }
}

void RubiksCube::draw() const {

    for (const t_cube & cube : this->_cubes)
        cube.mesh.draw();
}
