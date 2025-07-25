#pragma once
#include <vector>
#include <glad/glad.h>

class Objeto {
private:
    GLuint VAO, VBO;
    GLuint shaderProgram;
    size_t numVertices;

public:
    Objeto(const std::vector<float>& vertices, GLuint shaderProgram);
    ~Objeto();
    void dibujar() const;
};
