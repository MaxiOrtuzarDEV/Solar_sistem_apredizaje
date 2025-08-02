#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Objeto.h"
#include "src/shader/Shader.h"

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float heigthScreen = 800.0f;
float widthScreen = 1200.0f;

GLFWwindow* startGlfw();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint compileShader();
std::vector<float> generaCIRCLE_conColor(float radius, int segments, float r, float g, float b);

std::vector<float> triaguloVertex = {
     0.0f,   0.25f, -0.5f,   1.0f, 0.0f, 0.0f,   0.5f, 1.0f,
    -0.25f, -0.25f, -0.5f,   0.0f, 0.0f, 0.5f,   0.0f, 0.0f,
     0.25f, -0.25f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
};

int main() {
    GLFWwindow* window = startGlfw();
    if (!window) {
        return -1;
    }

    glViewport(0, 0, static_cast<int>(widthScreen), static_cast<int>(heigthScreen));

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cameraPosition(0.0f, 0.f, 3.0f);
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection(glm::normalize(cameraPosition- cameraTarget));
    glm::vec3 cameraRight(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection)));
    glm::vec3 cameraUp(glm::cross(cameraDirection, cameraRight));

    glm::mat4 viewer = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

    const GLuint shaderProgram = compileShader();
    Objeto triangulo(triaguloVertex, shaderProgram);

    // Configurar matrices de vista y proyección una sola vez
    glUseProgram(shaderProgram);

    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewer));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), widthScreen / heigthScreen, 0.1f, 100.0f);

    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    triangulo.setTexture("../assets/container.jpg");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.10f, 0.19f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dibujar triángulo estático primero
        glm::mat4 modelTriangulo = glm::mat4(1.0f);
        triangulo.setModelMatrix(modelTriangulo);


        // Dibujar triángulo en movimiento
        glm::mat4 modelTrianguloMovil = glm::mat4(1.0f);
        modelTrianguloMovil = glm::translate(modelTrianguloMovil, glm::vec3(
            0.0f,
            std::cos(static_cast<float>(glfwGetTime())),
            0.0f
        ));
        triangulo.setModelMatrix(modelTrianguloMovil);
        triangulo.dibujar();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLFWwindow* startGlfw() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(static_cast<int>(widthScreen), static_cast<int>(heigthScreen), "Hello World", nullptr, nullptr);

    if (!window) {
        std::cout << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

GLuint compileShader() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

