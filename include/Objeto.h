#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Texture {
    int widthTexture, heightTexture, nrChannels;
    GLuint textureID;
    unsigned char* imgData;
    bool tieneTexture = false;
};

class Objeto {
private:
    GLuint VAO, VBO;
    GLuint shaderProgram;
    std::vector<float> vertices;
    size_t numVertices;
    int vertexColorLocation;
    Texture texture;

public:
    Objeto(const std::vector<float>& vertices, GLuint shaderProgram);
    ~Objeto();
    void dibujar() const;
    void setModelMatrix(const glm::mat4& model) const;
    void setTexture(const char * texture_path);
};
