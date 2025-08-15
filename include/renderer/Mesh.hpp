#pragma once

#include <string>

#include <glm/glm.hpp>

struct Vertex {

    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoords;
};

class Shader;

class Mesh {

public:

    Mesh(const Shader & shader);
    ~Mesh();

    void init(const std::string gltPath);

    void translate(const glm::vec3 & offset);
    void rotate(const float angleRadians, const glm::vec3 & axis);
    void scale(const glm::vec3 & factor);

    void draw() const;

private:

    const Shader & _shader;

    glm::mat4 _model;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
    unsigned int _indexCount;

    unsigned int _texture;
};
