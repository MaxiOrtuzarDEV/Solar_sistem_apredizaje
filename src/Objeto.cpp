#include "Objeto.h"

#include "stb_image/stb_image.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Objeto::Objeto(const std::vector<float>& vertices, const GLuint shaderProgram)
    : shaderProgram(shaderProgram), vertices(vertices), numVertices(vertices.size() / 8) // Cambiado de 6 a 8
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void *>(nullptr)); // posición
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float))); // color
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float))); // coordenadas de textura
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Objeto::~Objeto() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (texture.tieneTexture) {
        glDeleteTextures(1, &texture.textureID); // Limpieza de textura
    }
}

void Objeto::dibujar() const {
    glUseProgram(shaderProgram);

    // Textura
    if (texture.tieneTexture) {
        glUniform1i(glGetUniformLocation(shaderProgram, "usarTextura"), true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.textureID);
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    } else {
        glUniform1i(glGetUniformLocation(shaderProgram, "usarTextura"), false);
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(numVertices));
}

void Objeto::setModelMatrix(const glm::mat4& model) const {
    glUseProgram(shaderProgram);
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Objeto::setTexture(const char* texture_path) {
    glUseProgram(shaderProgram);
    glGenTextures(1, &texture.textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.textureID);

    // Parámetros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); // Voltear imagen verticalmente
    unsigned char* imgData = stbi_load(texture_path, &texture.widthTexture, &texture.heightTexture, &texture.nrChannels, 0);

    if (imgData) {
        GLenum format = (texture.nrChannels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D,
            0, format,
            texture.widthTexture, texture.heightTexture,
            0, format, GL_UNSIGNED_BYTE, imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
        texture.tieneTexture = true;
    } else {
        std::cerr << "❌ Error al cargar textura: " << texture_path << std::endl;
    }

    stbi_image_free(imgData);
}