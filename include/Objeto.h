#pragma once
#include <vector>
#include <glad/glad.h>

class Objeto {
private:
    GLuint VAO, VBO;
    GLuint shaderProgram;
    size_t numVertices;
    int vertexColorLocation;

public:
    Objeto(const std::vector<float>& vertices, GLuint shaderProgram);
    ~Objeto();
    void dibujar() const;
    void updateColor(float redValue = 0.0f, float greenValue = 0.0f, float blueValue = 0.0f);
    void updateRedComponentColor(float redValue) const;
    void updateGreenComponentColor(float greenValue) const;
    void updateBlueComponentColor(float blueValue) const;
};
