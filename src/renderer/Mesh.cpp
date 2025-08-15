#include "renderer/Mesh.hpp"
#include "renderer/Renderer.hpp"

#include <iostream>

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include <gltf/tiny_gltf.h>

Mesh::Mesh(const Shader & shader) : _shader(shader) {}

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

void Mesh::init(const std::string gltPath) {

    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err, warn;

    bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, gltPath);

    if (!warn.empty())
        std::cout << "Warn: " << warn << std::endl;
    if (!err.empty())
        std::cerr << "Err: " << err << std::endl;
    if (!ret)
        throw std::runtime_error("Failed to load GLB");

    const tinygltf::Mesh & mesh = model.meshes[0];

    std::vector<Vertex> vertices;
    std::vector<unsigned short> allIndices;

    for (const auto & primitive : mesh.primitives) {

        glm::vec3 baseColor(1.0f);
        if (primitive.material >= 0 && primitive.material < static_cast<int>(model.materials.size())) {

            const auto & mat = model.materials[primitive.material];
            const auto & colorFactor = mat.pbrMetallicRoughness.baseColorFactor;

            if (colorFactor.size() >= 3)
                baseColor = glm::vec3(colorFactor[0], colorFactor[1], colorFactor[2]);
        }

        const auto & posAccessor = model.accessors.at(primitive.attributes.at("POSITION"));
        const auto & posView = model.bufferViews[posAccessor.bufferView];
        const auto & posBuffer = model.buffers[posView.buffer];
        const float * positions = reinterpret_cast<const float * >(&posBuffer.data[posView.byteOffset + posAccessor.byteOffset]);

        const float * uvs = nullptr;
        auto uvIt = primitive.attributes.find("TEXCOORD_0");

        if (uvIt != primitive.attributes.end()) {

            const auto & uvAccessor = model.accessors.at(uvIt->second);
            const auto & uvView = model.bufferViews[uvAccessor.bufferView];
            const auto & uvBuffer = model.buffers[uvView.buffer];
            uvs = reinterpret_cast<const float * >(&uvBuffer.data[uvView.byteOffset + uvAccessor.byteOffset]);
        }

        const auto & indexAccessor = model.accessors.at(primitive.indices);
        const auto & indexView = model.bufferViews[indexAccessor.bufferView];
        const auto & indexBuffer = model.buffers[indexView.buffer];
        const unsigned short * indices = reinterpret_cast<const unsigned short * >(&indexBuffer.data[indexView.byteOffset + indexAccessor.byteOffset]);

        size_t baseVertex = vertices.size();

        for (size_t i = 0; i < posAccessor.count; i++) {

            Vertex v;

            v.position = glm::vec3(positions[i*3], positions[i*3+1], positions[i*3+2]);
            v.texCoords = uvs ? glm::vec2(uvs[i*2], uvs[i*2+1]) : glm::vec2(0.0f);
            v.color = baseColor;
            vertices.push_back(v);
        }

        for (size_t i = 0; i < indexAccessor.count; i++)
            allIndices.push_back(static_cast<unsigned short>(baseVertex + indices[i]));
    }

    this->_indexCount = allIndices.size();

    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, allIndices.size() * sizeof(unsigned short), allIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);

    this->_model = glm::mat4(1.0f);
}

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

    this->_shader.setMat4(MODEL, this->_model);

    glBindVertexArray(this->_vao);

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, this->_texture);

    glDrawElements(GL_TRIANGLES, this->_indexCount, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}
