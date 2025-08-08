#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Vertex {

    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoords;
};

class Mesh {

public:

    Mesh(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);
    Mesh();
    ~Mesh();

    void init();

    const glm::mat4 & getModel() const;
    const unsigned int & getTexture() const;

    void translate(const glm::vec3 & offset);
    void rotate(const float angleRadians, const glm::vec3 & axis);
    void scale(const glm::vec3 & factor);

    void draw() const;

private:

    glm::mat4 _model;
    unsigned int _vao;
    unsigned int _vbo;
    unsigned int _ebo;
    unsigned int _indexCount;

    int imgSize[2];
    int numColCh;
    unsigned char * imgBytes;
    unsigned int _texture;
};
