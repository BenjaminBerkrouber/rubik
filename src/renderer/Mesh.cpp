#include "renderer/Mesh.hpp"
#include "renderer/Renderer.hpp"

#include <iostream>

#include <glad/gl.h>

#include <glm/gtc/matrix_transform.hpp>

#include <stb/stb_image.h>

Mesh::Mesh(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices) {

    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);

    this->_indexCount = static_cast<unsigned int>(indices.size());
}

Mesh::Mesh() {}

Mesh::~Mesh() {

    if (this->_ebo)
        glDeleteBuffers(1, &this->_ebo);
    if (this->_vbo)
        glDeleteBuffers(1, &this->_vbo);
    if (this->_vao)
        glDeleteVertexArrays(1, &this->_vao);
    if (this->_texture)
        glDeleteTextures(1, &this->_texture);
}

void Mesh::init() {

std::vector<Vertex> vertices = {
    // Face avant
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}}, // 0
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 0.0f}}, // 1
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f}}, // 2
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f}}, // 3

    // Face arrière
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // 4
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // 5
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}}, // 6
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}, // 7

    // Face gauche
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 8
    {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 9
    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // 10
    {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // 11

    // Face droite
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {0.0f, 0.0f}}, // 12
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 0.0f}}, // 13
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f}}, // 14
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {0.0f, 1.0f}}, // 15

    // Face supérieure
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {0.0f, 0.0f}}, // 16
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 0.0f}}, // 17
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f}}, // 18
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {0.0f, 1.0f}}, // 19

    // Face inférieure
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}, // 20
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}}, // 21
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}}, // 22
    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}, // 23
};


std::vector<unsigned int> indices = {
    // Avant
    0, 1, 2, 0, 2, 3,
    // Arrière
    4, 5, 6, 4, 6, 7,
    // Gauche
    8, 9,10, 8,10,11,
    // Droite
   12,13,14,12,14,15,
    // Haut
   16,17,18,16,18,19,
    // Bas
   20,21,22,20,22,23
};

    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
    this->_indexCount = static_cast<unsigned int>(indices.size());

    this->_model = glm::mat4(1.0f);


    stbi_set_flip_vertically_on_load(true);
    this->imgBytes = stbi_load("brick.png", &this->imgSize[WIDTH], &this->imgSize[HEIGHT], &this->numColCh, 0);

    glGenTextures(1, &this->_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->imgSize[WIDTH], this->imgSize[HEIGHT], 0, GL_RGBA, GL_UNSIGNED_BYTE, this->imgBytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(this->imgBytes);
    glBindTexture(GL_TEXTURE_2D, 0);
}

const glm::mat4 & Mesh::getModel() const {return (this->_model);}

const unsigned int & Mesh::getTexture() const {return (this->_texture);}

void Mesh::translate(const glm::vec3 & offset) {
    
    this->_model = glm::translate(this->_model, offset);
}

void Mesh::rotate(const float angleRadians, const glm::vec3 & axis) {
    
    this->_model = glm::rotate(this->_model, angleRadians, axis);
}

void Mesh::scale(const glm::vec3 & factor) {
    
    this->_model = glm::scale(this->_model, factor);
}

void Mesh::draw() const {

    glBindVertexArray(this->_vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_texture);

    glDrawElements(GL_TRIANGLES, this->_indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
