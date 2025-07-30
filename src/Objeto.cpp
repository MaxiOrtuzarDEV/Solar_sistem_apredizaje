#include "Objeto.h"

#include <GLFW/glfw3.h>

Objeto::Objeto(const std::vector<float>& vertices, GLuint shaderProgram)
    : shaderProgram(shaderProgram), numVertices(vertices.size() / 3) // asume 3 floats por vértice
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
}

Objeto::~Objeto() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Objeto::dibujar() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numVertices);
    glBindVertexArray(0);
}

void Objeto::updateColor(const float redValue, const float greenValue, const float blueValue) {
    glUseProgram(this->shaderProgram);
    glUniform4f(this->vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
}

void Objeto::updateRedComponentColor(const float redValue) const {
    glUseProgram(this->shaderProgram);
    glUniform4f(this->vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);
}

void Objeto::updateGreenComponentColor(const float greenValue) const {
    glUseProgram(this->shaderProgram);
    glUniform4f(this->vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

void Objeto::updateBlueComponentColor(const float blueValue) const {
    glUseProgram(this->shaderProgram);
    glUniform4f(this->vertexColorLocation, 0.0f, 0.0f, blueValue, 1.0f);
}

