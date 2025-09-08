#include "renderer/Shader.hpp"
#include "renderer/Mesh.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() {}

Shader::~Shader() {glDeleteProgram(this->_id);}

void Shader::init() {

    std::string vertSrc = _loadFromFile("src/_bonus/renderer/shaders/vertex.glsl");
    std::string fragSrc = _loadFromFile("src/_bonus/renderer/shaders/fragment.glsl");

    unsigned int vert = _compile(vertSrc, GL_VERTEX_SHADER);
    unsigned int frag = _compile(fragSrc, GL_FRAGMENT_SHADER);

    this->_id = glCreateProgram();
    glAttachShader(this->_id, vert);
    glAttachShader(this->_id, frag);
    glLinkProgram(this->_id);

    int success;
    glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
    if (!success) {

        char log[512];
        glGetProgramInfoLog(this->_id, 512, nullptr, log);
        std::cerr << "Shader link error:\n" << log << "\n";
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    glUseProgram(this->_id);

    this->_matLoc[MODEL] = glGetUniformLocation(this->_id, "model");
    this->_matLoc[CAMERA] = glGetUniformLocation(this->_id, "camMatrix");
    this->_matLoc[TEXTURE] = glGetUniformLocation(this->_id, "tex0");

    glUniform1i(this->_matLoc[TEXTURE], 0);
}

void Shader::setMat4(const int name, const glm::mat4 & mat) const {

    glUniformMatrix4fv(this->_matLoc[name], 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setTexture() const {

    glUniform1i(this->_matLoc[TEXTURE], 0);
}

std::string Shader::_loadFromFile(const std::string & path) {

    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();

    return (buffer.str());
}

unsigned int Shader::_compile(const std::string & src, unsigned int type) {

    const char * cstr = src.c_str();
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {

        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << "\n";
    }

    return (shader);
}
