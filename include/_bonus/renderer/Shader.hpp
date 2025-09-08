#pragma once

#include <string>
#include <glm/glm.hpp>

constexpr int MODEL = 0;
constexpr int CAMERA = 1;
constexpr int TEXTURE = 2;

class Mesh;

class Shader {

public:

    Shader();
    ~Shader();

    void init();
    void setMat4(const int name, const glm::mat4& mat) const;
    void setTexture() const;

private:

    unsigned int _id;
    int _matLoc[3];

    unsigned int _compile(const std::string & source, unsigned int type);
    std::string _loadFromFile(const std::string & path);
};
